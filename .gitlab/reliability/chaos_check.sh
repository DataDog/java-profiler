#!/usr/bin/env bash

set +e # Disable exit on error

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ROOT="$( cd "${HERE}/../.." >/dev/null 2>&1 && pwd )"

RUNTIME=${1}
CONFIG=${2:-profiler+tracer}
ALLOCATOR=${3:-gmalloc}

echo "Chaos run: runtime=${RUNTIME}s config=${CONFIG} allocator=${ALLOCATOR}"

CHAOS_JDK="${CHAOS_JDK:-21.0.3-tem}"
# CHAOS_JDK uses sdkman notation (<version>-<dist>); extract major for Adoptium API.
JDK_MAJOR="${CHAOS_JDK%%.*}"
JDK_ARCH=$(uname -m | sed 's/x86_64/x64/')
JDK_INSTALL_DIR="/opt/jdk-${CHAOS_JDK}"

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

if [ ! -x "${JDK_INSTALL_DIR}/bin/java" ]; then
  echo "FAIL:JDK ${CHAOS_JDK} not available after install" >&2
  exit 1
fi
export JAVA_HOME="${JDK_INSTALL_DIR}"
export PATH="${JAVA_HOME}/bin:${PATH}"
ACTIVE_JDK=$(java -version 2>&1 | head -1)
# Check major version only — patch may differ from the Adoptium latest GA.
if ! echo "${ACTIVE_JDK}" | grep -qE "\"${JDK_MAJOR}\."; then
  echo "FAIL:wrong JDK active (expected major ${JDK_MAJOR}, got: ${ACTIVE_JDK})" >&2
  exit 1
fi

# Resolve ddprof.jar: prefer local build artifact, fall back to Maven snapshot.
# Running mvn from /tmp avoids the empty pom.xml at the repo root.
DDPROF_JAR_LOCAL=$(ls "${ROOT}/ddprof-lib/build/libs/ddprof-"*.jar 2>/dev/null | head -1)
if [ -n "${DDPROF_JAR_LOCAL}" ] && [ -f "${DDPROF_JAR_LOCAL}" ]; then
  DDPROF_JAR="${DDPROF_JAR_LOCAL}"
  echo "Using local ddprof jar: ${DDPROF_JAR}"
else
  if [ -z "${CURRENT_VERSION:-}" ]; then
    echo "FAIL:CURRENT_VERSION is empty and no local jar found (get-versions dotenv missing)" >&2
    exit 1
  fi
  echo "Local ddprof jar not found — downloading ${CURRENT_VERSION} from Maven snapshots"
  (cd /tmp && mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
      -DrepoUrl=https://central.sonatype.com/repository/maven-snapshots/ \
      -Dartifact=com.datadoghq:ddprof:${CURRENT_VERSION})
  DDPROF_JAR="/root/.m2/repository/com/datadoghq/ddprof/${CURRENT_VERSION}/ddprof-${CURRENT_VERSION}.jar"
fi

if [ ! -f "${DDPROF_JAR}" ]; then
  echo "FAIL:ddprof jar unavailable" >&2
  exit 1
fi

mkdir -p /var/lib/datadog
wget -q --timeout=120 --tries=3 -O /var/lib/datadog/dd-java-agent.jar 'https://dtdg.co/latest-java-tracer'

# chaos.jar is produced once per pipeline by the chaos:build job (stresstest
# stage) and pulled here as an artifact. Fall back to an inline build if the
# artifact is absent (e.g. local repro outside CI).
CHAOS_JAR="${ROOT}/ddprof-stresstest/build/libs/chaos.jar"
if [ ! -f "${CHAOS_JAR}" ]; then
  echo "chaos.jar artifact not present — building inline"
  ( cd "${ROOT}" && ./gradlew :ddprof-stresstest:chaosJar -q )
fi

if [ ! -f "${CHAOS_JAR}" ]; then
  echo "FAIL:chaos.jar unavailable" >&2
  exit 1
fi

# Patch dd-java-agent.jar with the locally built ddprof contents so the agent's
# (relocated) profiler classes match the version under test.
DD_AGENT_JAR=/var/lib/datadog/dd-java-agent.jar \
DDPROF_JAR=${DDPROF_JAR} \
OUTPUT_JAR=/var/lib/datadog/dd-java-agent-patched.jar \
"${ROOT}/utils/patch-dd-java-agent.sh"

if [ ! -f /var/lib/datadog/dd-java-agent-patched.jar ]; then
  echo "FAIL:dd-java-agent patching failed" >&2
  exit 1
fi

PATCHED_AGENT=/var/lib/datadog/dd-java-agent-patched.jar

case $CONFIG in
  profiler)
    echo "Running with profiler only"
    ENABLEMENT="-Ddd.profiling.enabled=true -Ddd.trace.enabled=false"
    # @Trace is a no-op without the tracer, so trace-context is excluded here.
    ANTAGONISTS="thread-churn,alloc-storm,vthread-churn,classloader-churn,bounded-pool,context-hop,consumer-group,hidden-class-churn,direct-memory,weakref-wave,dump-storm"
    ;;
  profiler+tracer)
    echo "Running with profiler and tracer"
    ENABLEMENT="-Ddd.profiling.enabled=true -Ddd.trace.enabled=true"
    ANTAGONISTS="thread-churn,alloc-storm,vthread-churn,classloader-churn,trace-context,bounded-pool,context-hop,consumer-group,hidden-class-churn,direct-memory,weakref-wave,dump-storm"
    ;;
  *)
    echo "Unknown configuration: $CONFIG"
    exit 1
    ;;
esac

case $ALLOCATOR in
  gmalloc)
    echo "Running with gmalloc"
    ;;
  tcmalloc)
    echo "Running with tcmalloc"
    export LD_PRELOAD=$(find /usr/lib/ -name 'libtcmalloc_minimal.so.4')
    ;;
  jemalloc)
    echo "Running with jemalloc"
    export LD_PRELOAD=$(find /usr/lib/ -name 'libjemalloc.so')
    ;;
  *)
    echo "Unknown allocator: $ALLOCATOR"
    echo "Valid values are: gmalloc, tcmalloc, jemalloc"
    exit 1
    ;;
esac

echo "LD_PRELOAD=$LD_PRELOAD"

timeout "$((RUNTIME + 300))" \
java -javaagent:${PATCHED_AGENT} \
     ${ENABLEMENT} \
     -Ddd.profiling.upload.period=10 \
     -Ddd.profiling.start-force-first=true \
     -Ddd.profiling.ddprof.liveheap.enabled=true \
     -Ddd.profiling.ddprof.alloc.enabled=true \
     -Ddd.profiling.ddprof.wall.enabled=true \
     -Ddd.profiling.ddprof.nativemem.enabled=true \
     -Ddd.env=java-profiler-stability \
     -Ddd.service=java-profiler-chaos \
     -Xmx2g -Xms2g \
     -XX:MaxMetaspaceSize=384m \
     -XX:ErrorFile=${HERE}/../../hs_err.log \
     -XX:OnError="${HERE}/../../dd_crash_uploader.sh %p" \
     -jar ${CHAOS_JAR} \
     --duration ${RUNTIME}s \
     --antagonists ${ANTAGONISTS}

RC=$?
echo "RC=$RC"

if [ $RC -ne 0 ]; then
  echo "FAIL:Chaos harness crashed (RC=$RC)" >&2
  exit 1
fi
