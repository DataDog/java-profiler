#!/usr/bin/env bash

set +e # Disable exit on error

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

RUNTIME=${1}
CONFIG=${2:-profiler}
ALLOCATOR=${3:-gmalloc}

# Function to count CPUs from ranges and individual numbers
count_cpus() {
    local cpus=$(cat /sys/fs/cgroup/cpuset/cpuset.cpus)
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

curl -s "https://get.sdkman.io" | bash
source "/root/.sdkman/bin/sdkman-init.sh" 1>/dev/null 2>/dev/null

sdk install java 21.0.3-tem 1>/dev/null 2>/dev/null

mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
    -DrepoUrl=https://central.sonatype.com/repository/maven-snapshots/ \
    -Dartifact=com.datadoghq:ddprof:${CURRENT_VERSION} 1>/dev/null 2>/dev/null

mkdir -p /var/lib/datadog/${CURRENT_VERSION}
rm -rf /var/lib/datadog/${CURRENT_VERSION}/*

unzip -q -d /var/lib/datadog/${CURRENT_VERSION} /root/.m2/repository/com/datadoghq/ddprof/${CURRENT_VERSION}/ddprof-${CURRENT_VERSION}.jar
AGENT_LIB=$(find /var/lib/datadog/${CURRENT_VERSION} -name 'libjavaProfiler.so' | fgrep '/linux-x64/')

echo "Agent lib: ${AGENT_LIB}"
uname -a
echo "CPU Cores: $(count_cpus)"
echo "Run duration: ${RUNTIME} seconds"

wget -q -O /var/lib/datadog/dd-java-agent.jar 'https://dtdg.co/latest-java-tracer'

CONTROL_FILE=".running"
touch $CONTROL_FILE
sh ./benchmarks/steps/mem_watch.sh $CONTROL_FILE ${HERE}/../../memwatch.log &

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

java -javaagent:/var/lib/datadog/dd-java-agent.jar \
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
     -Dddprof.debug.malloc_arena_max=2 \
     -Xmx800m -Xms800m \
     -Dctl=$CONTROL_FILE \
     -XX:ErrorFile=${HERE}/../../hs_err.log \
     -jar /var/lib/benchmarks/renaissance.jar akka-uct -t ${RUNTIME}

RC=$?
echo "RC=$RC"
rm -f $CONTROL_FILE > /dev/null

if [ $RC -ne 0 ]; then
  echo "FAIL:Benchmark crashed" >&2
fi

LOG=$(python3 ${HERE}/memory_trend_check.py --output ${HERE}/../../memwatch-trend.png ${HERE}/../../memwatch.log)
echo "$LOG"

TREND=$(echo "$LOG" | grep "TREND:" | cut -f2 -d':')

if [ "$TREND" == "up" ]; then
  echo "FAIL:Memory usage is trending up" >&2
fi