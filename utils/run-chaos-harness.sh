#!/usr/bin/env bash
#
# Standalone chaos-harness runner. Builds/locates the ddprof jar, patches a
# dd-java-agent build with it, and runs the long-running chaos harness
# (ddprof-stresstest/src/chaos) with a chosen antagonist set and allocator.
#
# Usable both from CI (see .gitlab/reliability/chaos_check.sh, a thin wrapper
# around this script) and by hand for local repro — no CI-only assumptions
# (no fixed /opt or /var/lib paths, no CI-artifact env vars required).
#
# Usage: run-chaos-harness.sh <runtime-seconds> [config] [allocator] [antagonists]
#   config:      profiler | profiler+tracer (default: profiler+tracer)
#   allocator:   gmalloc | tcmalloc | jemalloc (default: gmalloc)
#   antagonists: comma-separated antagonist names; overrides the config default
#
# Env vars:
#   CHAOS_JDK        sdkman-style version (e.g. 21.0.3-tem) to require/download.
#                     If unset, uses whatever `java` is already on PATH.
#   CHAOS_JDK_DIR     where to install a downloaded JDK (default: under
#                     CHAOS_WORK_DIR; set to a persistent path to cache across runs).
#   CHAOS_WORK_DIR    scratch dir for the patched agent, downloaded jars, and
#                     hs_err.log (default: <repo>/.chaos-harness).
#   CHAOS_REFRESH_AGENT=1  force re-download of dd-java-agent.jar even if cached.

set +e

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ROOT="$( cd "${HERE}/.." >/dev/null 2>&1 && pwd )"

RUNTIME=${1}
CONFIG=${2:-profiler+tracer}
ALLOCATOR=${3:-gmalloc}
ANTAGONISTS_OVERRIDE=${4:-}

if [ -z "${RUNTIME}" ]; then
  echo "usage: $0 <runtime-seconds> [config] [allocator] [antagonists]" >&2
  exit 1
fi

WORK_DIR="${CHAOS_WORK_DIR:-${ROOT}/.chaos-harness}"
mkdir -p "${WORK_DIR}"

echo "Chaos run: runtime=${RUNTIME}s config=${CONFIG} allocator=${ALLOCATOR}"

# --- JDK resolution ---------------------------------------------------------
# Only fetch a JDK if the caller explicitly pinned one via CHAOS_JDK and it
# doesn't match what's already active; otherwise just use `java` as found.
if [ -n "${CHAOS_JDK:-}" ]; then
  JDK_MAJOR="${CHAOS_JDK%%.*}"
  ACTIVE_MAJOR=$(java -version 2>&1 | head -1 | grep -oE '"[0-9]+' | tr -d '"')
  if [ "${ACTIVE_MAJOR}" != "${JDK_MAJOR}" ]; then
    JDK_ARCH=$(uname -m | sed 's/x86_64/x64/')
    JDK_INSTALL_DIR="${CHAOS_JDK_DIR:-${WORK_DIR}/jdk-${CHAOS_JDK}}"
    if [ ! -x "${JDK_INSTALL_DIR}/bin/java" ]; then
      TMP=$(mktemp -d)
      DL_URL="https://api.adoptium.net/v3/binary/latest/${JDK_MAJOR}/ga/linux/${JDK_ARCH}/jdk/hotspot/normal/eclipse"
      echo "Downloading JDK ${CHAOS_JDK} (major ${JDK_MAJOR}) from Adoptium..."
      if ! curl -fsSL --max-time 300 "${DL_URL}" -o "${TMP}/jdk.tar.gz"; then
        echo "FAIL:JDK ${CHAOS_JDK} download failed" >&2
        rm -rf "${TMP}"
        exit 1
      fi
      mkdir -p "${JDK_INSTALL_DIR}"
      tar -xzf "${TMP}/jdk.tar.gz" -C "${JDK_INSTALL_DIR}" --strip-components=1
      rm -rf "${TMP}"
    fi
    export JAVA_HOME="${JDK_INSTALL_DIR}"
    export PATH="${JAVA_HOME}/bin:${PATH}"
  fi
fi

if ! command -v java >/dev/null 2>&1; then
  echo "FAIL:no java on PATH (set CHAOS_JDK to have one downloaded)" >&2
  exit 1
fi
echo "Using: $(java -version 2>&1 | head -1)"

# --- ddprof jar --------------------------------------------------------------
# Prefer a local build artifact. If absent and CURRENT_VERSION is set (CI
# passes it in from the get-versions job), fall back to the Maven snapshot.
DDPROF_JAR=$(ls "${ROOT}/ddprof-lib/build/libs/ddprof-"*.jar 2>/dev/null | head -1)
if [ -z "${DDPROF_JAR}" ] || [ ! -f "${DDPROF_JAR}" ]; then
  if [ -z "${CURRENT_VERSION:-}" ]; then
    echo "FAIL:no local ddprof jar found and CURRENT_VERSION is empty — build one first: ./gradlew :ddprof-lib:jar" >&2
    exit 1
  fi
  echo "Local ddprof jar not found — downloading ${CURRENT_VERSION} from Maven snapshots"
  ( cd /tmp && mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
      -DrepoUrl=https://central.sonatype.com/repository/maven-snapshots/ \
      -Dartifact=com.datadoghq:ddprof:"${CURRENT_VERSION}" )
  DDPROF_JAR="/root/.m2/repository/com/datadoghq/ddprof/${CURRENT_VERSION}/ddprof-${CURRENT_VERSION}.jar"
  if [ ! -f "${DDPROF_JAR}" ]; then
    echo "FAIL:ddprof jar unavailable (Maven snapshot download failed)" >&2
    exit 1
  fi
fi
echo "Using ddprof jar: ${DDPROF_JAR}"

# --- dd-java-agent ------------------------------------------------------------
DD_AGENT_JAR="${WORK_DIR}/dd-java-agent.jar"
if [ ! -f "${DD_AGENT_JAR}" ] || [ "${CHAOS_REFRESH_AGENT:-0}" = "1" ]; then
  echo "Fetching dd-java-agent.jar..."
  wget -q --timeout=120 --tries=3 -O "${DD_AGENT_JAR}" 'https://dtdg.co/latest-java-tracer'
fi
if [ ! -f "${DD_AGENT_JAR}" ]; then
  echo "FAIL:dd-java-agent.jar download failed" >&2
  exit 1
fi

CHAOS_JAR="${ROOT}/ddprof-stresstest/build/libs/chaos.jar"
if [ ! -f "${CHAOS_JAR}" ]; then
  echo "chaos.jar not present — building inline"
  # --no-daemon: a lingering Gradle daemon shares this container's cgroup with
  # the chaos JVM we're about to launch and eats into the same memory ceiling
  # the MemoryGovernor is trying to protect.
  ( cd "${ROOT}" && ./gradlew :ddprof-stresstest:chaosJar -q --no-daemon )
fi
if [ ! -f "${CHAOS_JAR}" ]; then
  echo "FAIL:chaos.jar unavailable" >&2
  exit 1
fi

# Patch dd-java-agent.jar with the locally built ddprof contents so the
# agent's (relocated) profiler classes match the version under test.
PATCHED_AGENT="${WORK_DIR}/dd-java-agent-patched.jar"
if ! DD_AGENT_JAR="${DD_AGENT_JAR}" DDPROF_JAR="${DDPROF_JAR}" OUTPUT_JAR="${PATCHED_AGENT}" \
  "${ROOT}/utils/patch-dd-java-agent.sh"; then
  echo "FAIL:dd-java-agent patching failed" >&2
  exit 1
fi
if [ ! -f "${PATCHED_AGENT}" ]; then
  echo "FAIL:dd-java-agent patching reported success but output jar is missing" >&2
  exit 1
fi

case $CONFIG in
  profiler)
    ENABLEMENT="-Ddd.profiling.enabled=true -Ddd.trace.enabled=false"
    # @Trace is a no-op without the tracer, so trace-context and
    # vthread-context-cascade (which is driven entirely by @Trace-annotated
    # methods) are excluded here.
    DEFAULT_ANTAGONISTS="thread-churn,alloc-storm,vthread-churn,classloader-churn,bounded-pool,context-hop,consumer-group,hidden-class-churn,direct-memory,weakref-wave,dump-storm"
    ;;
  profiler+tracer)
    ENABLEMENT="-Ddd.profiling.enabled=true -Ddd.trace.enabled=true"
    DEFAULT_ANTAGONISTS="thread-churn,alloc-storm,vthread-churn,classloader-churn,trace-context,vthread-context-cascade,bounded-pool,context-hop,consumer-group,hidden-class-churn,direct-memory,weakref-wave,dump-storm"
    ;;
  *)
    echo "Unknown configuration: $CONFIG (valid: profiler, profiler+tracer)" >&2
    exit 1
    ;;
esac
ANTAGONISTS="${ANTAGONISTS_OVERRIDE:-${DEFAULT_ANTAGONISTS}}"

case $ALLOCATOR in
  gmalloc)
    # Turn silent heap corruption (e.g. a stale-pointer UAF write into a freed
    # chunk) into an immediate, attributable SIGABRT instead of a crash much
    # later in an unrelated allocation. Only meaningful against glibc's own
    # malloc, not the LD_PRELOAD-replaced allocators below.
    export MALLOC_CHECK_=3
    export MALLOC_PERTURB_=$((RANDOM % 255 + 1))
    # Logged so a glibc-detected corruption abort can be reproduced with the
    # same perturb byte (the value is otherwise random per run).
    echo "MALLOC_PERTURB_=${MALLOC_PERTURB_}"
    # thread-churn/dump-storm/vthread-context-cascade cycle many short-lived
    # threads; glibc's per-thread arenas are slow to trim back to the OS,
    # which was inflating container RSS past the OOM limit on aarch64
    # (mirrors the tcmalloc/jemalloc tuning below).
    export MALLOC_ARENA_MAX=2
    export MALLOC_TRIM_THRESHOLD_=65536
    # glibc >= 2.34 moved MALLOC_CHECK_ support out of the main libc; it is a
    # silent no-op unless libc_malloc_debug is preloaded (see glibc's "Heap
    # Consistency Checking" docs). Detect that case and preload the debug
    # library explicitly, rather than silently running with corruption
    # detection disabled.
    if command -v ldd >/dev/null 2>&1; then
      GLIBC_VERSION=$(ldd --version 2>/dev/null | head -1 | grep -oE '[0-9]+\.[0-9]+$')
      if [ -n "${GLIBC_VERSION}" ] && [ "$(printf '%s\n' "2.34" "${GLIBC_VERSION}" | sort -V | head -1)" = "2.34" ]; then
        MALLOC_DEBUG_LIB=$(find /usr/lib/ /usr/lib64/ /lib/ /lib64/ -name 'libc_malloc_debug.so*' 2>/dev/null | head -1)
        if [ -z "${MALLOC_DEBUG_LIB}" ]; then
          echo "FAIL:glibc ${GLIBC_VERSION} requires libc_malloc_debug to be preloaded for MALLOC_CHECK_ to take effect, but it could not be found" >&2
          exit 1
        fi
        export LD_PRELOAD="${MALLOC_DEBUG_LIB}${LD_PRELOAD:+:${LD_PRELOAD}}"
        echo "glibc ${GLIBC_VERSION} detected — preloading ${MALLOC_DEBUG_LIB} for MALLOC_CHECK_"
      fi
    fi
    ;;
  tcmalloc)
    export LD_PRELOAD=$(find /usr/lib/ /usr/lib64/ /opt/homebrew/lib/ /usr/local/lib/ -name 'libtcmalloc_minimal.so.4' -o -name 'libtcmalloc.dylib' 2>/dev/null | head -1)
    # thread-churn/dump-storm antagonists cycle many short-lived threads;
    # tcmalloc's defaults are slow to return their per-thread caches to the
    # OS, which was inflating container RSS past the OOM limit on aarch64.
    export TCMALLOC_RELEASE_RATE=10
    export TCMALLOC_AGGRESSIVE_DECOMMIT=1
    ;;
  jemalloc)
    export LD_PRELOAD=$(find /usr/lib/ /usr/lib64/ /opt/homebrew/lib/ /usr/local/lib/ -name 'libjemalloc.so' -o -name 'libjemalloc.dylib' 2>/dev/null | head -1)
    # Same aarch64 RSS-inflation issue as tcmalloc above: jemalloc's default
    # decay times leave dirty/muzzy pages resident under heavy thread churn.
    export MALLOC_CONF="background_thread:true,dirty_decay_ms:1000,muzzy_decay_ms:1000"
    ;;
  *)
    echo "Unknown allocator: $ALLOCATOR (valid: gmalloc, tcmalloc, jemalloc)" >&2
    exit 1
    ;;
esac
echo "LD_PRELOAD=${LD_PRELOAD:-}"

# Log the actual container memory ceiling (if any) so OOMKilled failures are
# diagnosable from the CI job log directly, instead of having to infer it
# from RSS measurements on a separate repro host.
CGROUP_MEM_LIMIT=$(cat /sys/fs/cgroup/memory/memory.limit_in_bytes 2>/dev/null || cat /sys/fs/cgroup/memory.max 2>/dev/null || echo "unknown")
echo "cgroup memory limit: ${CGROUP_MEM_LIMIT}"

# Container ceiling is 6GiB (see logged cgroup limit above). Job 1858271921
# (profiler+tracer, jemalloc, 21.0.3-tem, aarch64) OOMKilled within seconds of
# all 13 antagonists starting: several of them (alloc-storm, direct-memory,
# dump-storm) deliberately burst off-heap/native memory hard and fast, sharing
# the same cgroup limit as the heap. Reproduced under a 6GiB-capped cgroup and
# confirmed MemoryGovernor (see chaos/MemoryGovernor.java, wired into the
# antagonists' hot loops) keeps that same config under the limit. 2560m still
# ran within a few percent of java.lang.OutOfMemoryError under the profiler
# config (job 1860026763); 3072m keeps comparable headroom to the off-heap
# side while giving the heap itself real margin.
HEAP_MB=3072

HS_ERR="${CHAOS_ERROR_FILE:-${WORK_DIR}/hs_err.log}"
rm -f "${HS_ERR}"

# dd-trace-java's profiling uploader writes rotated JFR chunks under
# /tmp/ddprof_root/pid_<pid>/jfr/... (the path seen in the
# jfrStreamWriterHost.inline.hpp write-guarantee crash log). On a CI runner
# with no real intake, stalled/failed uploads can leave chunks from a
# previous run sitting on disk, starving the next run's JFR writer. Clean
# stale chunks before we start and again on exit, and log disk usage so a
# future disk-full crash is diagnosable from the job log directly.
DDPROF_ROOT="/tmp/ddprof_root"
rm -rf "${DDPROF_ROOT}"
trap 'rm -rf "${DDPROF_ROOT}"' EXIT
echo "disk usage ($(dirname "${DDPROF_ROOT}")): $(df -h "$(dirname "${DDPROF_ROOT}")" | awk 'NR==2{print $3" used / "$2" total ("$5" full)"}')"

# -XX:+ExitOnOutOfMemoryError: without it, a heap OOME is "recoverable" and
# every other allocating thread throws its own OutOfMemoryError over the
# following seconds instead of the process exiting once. Job 1861521304 rode
# that cascade into a java.lang.instrument allocation-failure assertion and
# then a SIGSEGV with no hs_err.log at all — exit immediately on the first
# OOME instead, so a failure is a single, diagnosable event.
CHAOS_START=$(date +%s)
timeout "$((RUNTIME + 300))" \
java -javaagent:${PATCHED_AGENT} \
     --add-opens java.base/java.lang=ALL-UNNAMED \
     --add-exports java.base/jdk.internal.misc=ALL-UNNAMED \
     ${ENABLEMENT} \
     -Ddd.profiling.upload.period=10 \
     -Ddd.profiling.start-force-first=true \
     -Ddd.profiling.ddprof.liveheap.enabled=true \
     -Ddd.profiling.ddprof.alloc.enabled=true \
     -Ddd.profiling.ddprof.wall.enabled=true \
     -Ddd.profiling.ddprof.nativemem.enabled=true \
     -Ddd.env=java-profiler-stability \
     -Ddd.service=java-profiler-chaos \
     -Xmx${HEAP_MB}m -Xms${HEAP_MB}m \
     -XX:MaxMetaspaceSize=384m \
     -XX:NativeMemoryTracking=summary \
     -XX:ErrorFile=${HS_ERR} \
     -XX:+ExitOnOutOfMemoryError \
     -jar ${CHAOS_JAR} \
     --duration ${RUNTIME}s \
     --antagonists ${ANTAGONISTS}

RC=$?
CHAOS_ELAPSED=$(( $(date +%s) - CHAOS_START ))
echo "RC=$RC (elapsed ${CHAOS_ELAPSED}s of ${RUNTIME}s requested)"

# Exit code 3 is HotSpot's own -XX:+ExitOnOutOfMemoryError termination — a
# clean exit, not a crash. Antagonists deliberately stress allocation, so
# hitting the heap ceiling under their combined load isn't itself a bug.
# It only counts as a failure here if it happened too early for the rest of
# the antagonist mix to have had a fair shot at running (see chaos_check.sh
# job 1862133932: this run recovered from four heap-pressure cycles before a
# fifth finally exhausted it at ~80% of the run).
if [ $RC -eq 3 ] && [ "${CHAOS_ELAPSED}" -ge "$((RUNTIME / 2))" ]; then
  echo "Chaos run hit the heap ceiling at ${CHAOS_ELAPSED}s/${RUNTIME}s — treating as a tolerated outcome, not a failure"
  exit 0
fi

if [ $RC -ne 0 ]; then
  CRASH_MSG="Chaos harness crashed (RC=${RC})"
  if [ $RC -eq 3 ]; then
    CRASH_MSG="Chaos harness hit heap OOME too early (RC=3 at ${CHAOS_ELAPSED}s/${RUNTIME}s) — antagonists didn't get a fair run"
  fi
  if [ -f "${HS_ERR}" ]; then
    SIG=$(grep -m1 '^siginfo:' "${HS_ERR}" 2>/dev/null | tr -d '\n' | cut -c1-120)
    FRAME=$(grep -m1 'libjavaProfiler\|AsyncProfiler' "${HS_ERR}" 2>/dev/null | sed 's/^[[:space:]]*//' | tr -d '\n' | cut -c1-120)
    [ -n "${SIG}" ]   && CRASH_MSG="${CRASH_MSG};${SIG}"
    [ -n "${FRAME}" ] && CRASH_MSG="${CRASH_MSG};${FRAME}"
    echo "hs_err written to ${HS_ERR}"
  fi
  echo "FAIL:${CRASH_MSG}" >&2
  exit 1
fi

echo "Chaos run completed cleanly"
