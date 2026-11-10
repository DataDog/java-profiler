#!/usr/bin/env bash

set +e # Disable exit on error

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# shellcheck disable=SC1091  # marker tokens come from the sampler's helper
. "${HERE}/../benchmarks/steps/collect_markers.sh"

# Provisional; the JVM outlives the measured window by this tail, keeping
# about 24 pre-probe samples at RUNTIME=120 while the probe fits in the run.
PROBE_TAIL_SECONDS=30
# Provisional; must stay below PROBE_TAIL_SECONDS so the probe cannot
# outlive the JVM.
PROBE_TIMEOUT_SECONDS=20

# shellcheck disable=SC2155,SC2086  # preserved pre-existing CPU counting
# Function to count CPUs from ranges and individual numbers
count_cpus() {
    local cpuset_file="/sys/fs/cgroup/cpuset/cpuset.cpus"
    if [ ! -f "$cpuset_file" ] && [ -f /sys/fs/cgroup/cgroup.controllers ]; then
        cpuset_file="/sys/fs/cgroup/cpuset.cpus.effective"
    fi
    if [ ! -f "$cpuset_file" ]; then
        nproc
        return
    fi
    local cpus=$(cat "$cpuset_file")
    local cpu_count=0
    local IFS=','  # Use comma as delimiter to split ranges and numbers

    # Iterate over ranges and numbers
    for range in $cpus; do
        if [[ "$range" =~ - ]]; then
            # It's a range, calculate the number of CPUs in the range
            local start_cpu=$(echo $range | cut -d '-' -f 1)
            local end_cpu=$(echo $range | cut -d '-' -f 2)
            local num_cpus=$((end_cpu - start_cpu + 1))
            cpu_count=$((cpu_count + num_cpus))
        else
            # It's a single CPU number
            cpu_count=$((cpu_count + 1))
        fi
    done

    echo $cpu_count
}

# True while pid $1 is a live process; an exited child (reaped or zombie)
# counts as gone.
process_alive() {
    local state
    state=$(ps -o stat= -p "$1" 2>/dev/null | tr -d '[:space:]')
    [ -n "$state" ] && [ "$state" != "Z" ]
}

# Closes the measured window after $1 seconds or when JVM pid $2 exits
# early, then removes control file $4 and waits for sampler pid $3, so no
# mem line can be written during or after the probe.
close_measurement_window() {
    local runtime=$1 jvm_pid=$2 sampler_pid=$3 ctl_file=$4 deadline
    deadline=$(( $(date +%s) + runtime ))
    while :; do
        [ "$(date +%s)" -ge "$deadline" ] && break
        process_alive "$jvm_pid" || break
        sleep 1
    done
    rm -f "$ctl_file" > /dev/null
    wait "$sampler_pid"
}

# Prints the Rss kB of pid $2 under proc root $1, or NA when unreadable.
probe_rss_kb() {
    local rss
    rss=$(sed -n 's/^Rss:[[:space:]]*\([0-9][0-9]*\).*/\1/p' "$1/$2/smaps_rollup" 2>/dev/null)
    if [ -n "$rss" ]; then
        printf '%s\n' "$rss"
    else
        printf 'NA\n'
    fi
}

# Writes the release-probe records for allocator $1 and JVM pid $2 to log
# $3. jcmd attaches from outside the JVM and every marker is read from
# the proc and cgroup trees; nothing runs inside the JVM.
release_probe_records() {
    local allocator=$1 pid=$2 log=$3 status out rss
    local proc_root=${MEMWATCH_PROC_ROOT:-/proc}
    local cgroup_root=${MEMWATCH_CGROUP_ROOT:-/sys/fs/cgroup}
    # Derived from the java that launched the JVM, so the probe cannot
    # drift to another JDK through a probe-time PATH lookup.
    local jcmd=${MEM_TREND_JCMD:-$(dirname "$JAVA_BIN")/jcmd}
    if [ "$allocator" != "gmalloc" ]; then
        echo "release_probe=not-applicable allocator=${allocator}" >> "$log"
        return
    fi
    rss=$(probe_rss_kb "$proc_root" "$pid")
    echo "probe_before: rss_kb=${rss} $(collect_markers "$proc_root" "$cgroup_root" "$pid" $$)" >> "$log"
    # An absent or non-executable jcmd fails the probe, which maps to
    # inconclusive, exactly like a jcmd that errors or times out.
    status=failed
    if [ -x "$jcmd" ]; then
        if out=$(timeout "$PROBE_TIMEOUT_SECONDS" "$jcmd" "$pid" System.trim_native_heap 2>/dev/null) && \
           printf '%s\n' "$out" | grep -q 'Trim native heap:'; then
            status=ok
        fi
    fi
    echo "release_probe=jcmd status=${status}" >> "$log"
    rss=$(probe_rss_kb "$proc_root" "$pid")
    echo "probe_after: rss_kb=${rss} $(collect_markers "$proc_root" "$cgroup_root" "$pid" $$)" >> "$log"
}

# Emits at most one stderr line for verdict $1 with reason $2 on allocator
# $3; an absent verdict maps to inconclusive.
emit_verdict() {
    local verdict=$1 reason=$2 allocator=$3
    case "$verdict" in
        fail)
            if [ "$allocator" = "gmalloc" ]; then
                echo "FAIL:${reason}" >&2
            else
                echo "FAIL:Memory usage is trending up" >&2
            fi
            ;;
        inconclusive)
            echo "INCONCLUSIVE:${reason}" >&2
            ;;
        pass)
            ;;
        *)
            echo "INCONCLUSIVE:trend check produced no verdict" >&2
            ;;
    esac
}

# Runs the trend check on log $1 with plot output $2 for allocator $3,
# relays its output and maps its verdict to stderr. A non-zero interpreter
# exit is an infrastructure break, so it fails the job loudly instead of
# degrading to an inconclusive row.
run_trend_check() {
    local log=$1 png=$2 allocator=$3 out verdict reason rc
    local python_bin=${MEM_TREND_PYTHON:-python3}
    out=$("$python_bin" "${HERE}/memory_trend_check.py" --output "$png" --allocator "$allocator" "$log")
    rc=$?
    echo "$out"
    if [ "$rc" -ne 0 ]; then
        echo "FAIL:Trend check crashed" >&2
        return
    fi
    verdict=$(printf '%s\n' "$out" | grep -m1 '^VERDICT:' | cut -f2 -d':')
    reason=$(printf '%s\n' "$out" | grep -m1 '^VERDICT_REASON:' | sed 's/^VERDICT_REASON://')
    emit_verdict "$verdict" "$reason" "$allocator"
}

# Sourcing defines the helpers only; the gate itself runs when executed.
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
    RUNTIME=${1}
    CONFIG=${2:-profiler}
    ALLOCATOR=${3:-gmalloc}

    curl -s "https://get.sdkman.io" | bash
    # shellcheck disable=SC1091  # installed by the sdkman step above
    source "/root/.sdkman/bin/sdkman-init.sh" 1>/dev/null 2>/dev/null

    sdk install java 21.0.3-tem 1>/dev/null 2>/dev/null

    # Resolved once, before the JVM launch, so the probe jcmd comes from
    # the JDK that actually runs the JVM.
    JAVA_BIN=$(command -v java)

    DDPROF_JAR="/root/.m2/repository/com/datadoghq/ddprof/${CURRENT_VERSION}/ddprof-${CURRENT_VERSION}.jar"
    # Capture mvn's actual output (not just presence/absence of the jar) so a
    # genuine failure (auth, 404, blocked network) is visible instead of looking
    # like a transient miss.
    MVN_GET_LOG="${HERE}/../../maven-get.log"
    : > "$MVN_GET_LOG"
    # shellcheck disable=SC2086  # preserved pre-existing mvn invocation
    for attempt in 1 2 3 4 5 6; do
      echo "=== mvn get attempt ${attempt}/6 ===" >> "$MVN_GET_LOG"
      mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
          -DrepoUrl=https://central.sonatype.com/repository/maven-snapshots/ \
          -Dartifact=com.datadoghq:ddprof:${CURRENT_VERSION} >> "$MVN_GET_LOG" 2>&1
      [ -f "$DDPROF_JAR" ] && break
      echo "ddprof ${CURRENT_VERSION} not yet resolvable (attempt ${attempt}/6), retrying in 20s"
      sleep 20
    done
    if [ ! -f "$DDPROF_JAR" ]; then
      echo "FAIL:Could not fetch ddprof ${CURRENT_VERSION} jar" >&2
      echo "--- last mvn get output (see maven-get.log artifact for full history) ---" >&2
      tail -n 40 "$MVN_GET_LOG" >&2
      exit 1
    fi

    # shellcheck disable=SC2086  # preserved pre-existing artifact handling
    mkdir -p /var/lib/datadog/${CURRENT_VERSION}
    # shellcheck disable=SC2086  # preserved pre-existing artifact handling
    rm -rf /var/lib/datadog/${CURRENT_VERSION}/*

    # shellcheck disable=SC2086  # preserved pre-existing artifact handling
    unzip -q -d /var/lib/datadog/${CURRENT_VERSION} "$DDPROF_JAR"
    # shellcheck disable=SC2086,SC2197  # preserved pre-existing artifact handling
    AGENT_LIB=$(find /var/lib/datadog/${CURRENT_VERSION} -name 'libjavaProfiler.so' | fgrep '/linux-x64/')
    if [ -z "$AGENT_LIB" ]; then
      echo "FAIL:Could not locate libjavaProfiler.so for linux-x64" >&2
      exit 1
    fi

    echo "Agent lib: ${AGENT_LIB}"
    uname -a
    echo "CPU Cores: $(count_cpus)"
    echo "Run duration: ${RUNTIME} seconds"

    wget -q -O /var/lib/datadog/dd-java-agent.jar 'https://dtdg.co/latest-java-tracer'

    CONTROL_FILE=".running"
    touch $CONTROL_FILE
    case $CONFIG in
      profiler)
        echo "Running with profiler"
        ENABLEMENT="-Ddd.profiling.enabled=true -Ddd.trace.enabled=false"
        ;;
      profiler+tracer)
        echo "Running with profiler and tracer"
        ENABLEMENT="-Ddd.profiling.enabled=true -Ddd.trace.enabled=true"
        ;;
      *)
        echo "Unknown configuration: $CONFIG"
        exit 1
        ;;
    esac

    # shellcheck disable=SC2155  # preserved pre-existing LD_PRELOAD exports
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

    # shellcheck disable=SC2086  # preserved pre-existing JVM invocation
    "$JAVA_BIN" -javaagent:/var/lib/datadog/dd-java-agent.jar \
         $ENABLEMENT \
         -Ddd.profiling.upload.period=5 \
         -Ddd.profiling.start-force-first=true \
         -Ddd.profiling.ddprof.liveheap.enabled=true \
         -Ddd.profiling.ddprof.alloc.enabled=true \
         -Ddd.profiling.dprof.wall.enabled=true \
         -Ddd.integration.renaissance.enabled=true \
         -Ddd.env=java-profiler-stability \
         -Ddd.service=java-profiler-memory-trend \
         -Ddd.profiling.ddprof.debug.lib="${AGENT_LIB}" \
         -Xmx800m -Xms800m \
         -XX:MaxMetaspaceSize=384m \
         -Dctl=$CONTROL_FILE \
         -XX:ErrorFile=${HERE}/../../hs_err.log \
         -jar /var/lib/benchmarks/renaissance.jar akka-uct -t $((RUNTIME + PROBE_TAIL_SECONDS)) &
    JVM_PID=$!

    # The launched JVM's authoritative pid replaces the sampler's ps text
    # match, which can select a sibling process carrying the same tokens.
    export MEMWATCH_TARGET_PID="${JVM_PID}"
    # env -u keeps the allocator preload off the sampler's discovery pipeline
    # shellcheck disable=SC2086  # preserved pre-existing sampler launch
    env -u LD_PRELOAD sh ${HERE}/../benchmarks/steps/mem_watch.sh $CONTROL_FILE ${HERE}/../../memwatch.log &
    SAMPLER_PID=$!

    close_measurement_window "${RUNTIME}" "${JVM_PID}" "${SAMPLER_PID}" "${CONTROL_FILE}"
    release_probe_records "$ALLOCATOR" "${JVM_PID}" "${HERE}/../../memwatch.log"

    wait "${JVM_PID}"
    RC=$?
    echo "RC=$RC"

    if [ $RC -ne 0 ]; then
      echo "FAIL:Benchmark crashed" >&2
    fi

    run_trend_check "${HERE}/../../memwatch.log" "${HERE}/../../memwatch-trend.png" "$ALLOCATOR"
fi
