#!/usr/bin/env bash

set +e # Disable exit on error

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

RUNTIME=${1}
CONFIG=${2:-profiler}
ALLOCATOR=${3:-gmalloc}

echo "JIT Stability Check with runtime: ${RUNTIME} seconds, config=${CONFIG}"

curl -s "https://get.sdkman.io" | bash
source "/root/.sdkman/bin/sdkman-init.sh" 1>/dev/null 2>/dev/null

sdk install java 21.0.3-tem 1>/dev/null 2>/dev/null

DDPROF_JAR="/root/.m2/repository/com/datadoghq/ddprof/${CURRENT_VERSION}/ddprof-${CURRENT_VERSION}.jar"
# Capture mvn's actual output (not just presence/absence of the jar) so a
# genuine failure (auth, 404, blocked network) is visible instead of looking
# like a transient miss.
MVN_GET_LOG="${HERE}/../../maven-get.log"
: > "$MVN_GET_LOG"
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

mkdir -p /var/lib/datadog/${CURRENT_VERSION}
rm -rf /var/lib/datadog/${CURRENT_VERSION}/*

unzip -q -d /var/lib/datadog/${CURRENT_VERSION} "$DDPROF_JAR"
AGENT_LIB=$(find /var/lib/datadog/${CURRENT_VERSION} -name 'libjavaProfiler.so' | fgrep '/linux-x64/')
if [ -z "$AGENT_LIB" ]; then
  echo "FAIL:Could not locate libjavaProfiler.so for linux-x64" >&2
  exit 1
fi

echo "Agent lib: ${AGENT_LIB}"
uname -a
echo "Run duration: ${RUNTIME} seconds"

wget -q -O /var/lib/datadog/dd-java-agent.jar 'https://dtdg.co/latest-java-tracer'

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

start_time=$(date +%s)

while true; do
  # Get the current time
  current_time=$(date +%s)

  # Calculate the elapsed time
  elapsed_time=$((current_time - start_time))

  # Break the loop if the elapsed time is greater than or equal to the duration
  if ((elapsed_time >= ${RUNTIME})); then
    break
  fi

  java -javaagent:/var/lib/datadog/dd-java-agent.jar \
       $ENABLEMENT \
       -Ddd.profiling.upload.period=1 \
       -Ddd.profiling.start-force-first=true \
       -Ddd.profiling.ddprof.liveheap.enabled=true \
       -Ddd.profiling.ddprof.alloc.enabled=true \
       -Ddd.profiling.dprof.wall.enabled=true \
       -Ddd.integration.renaissance.enabled=true \
       -Ddd.env=java-profiler-stability \
        -Ddd.service=java-profiler-jit-stability \
       -Ddd.profiling.ddprof.debug.lib="${AGENT_LIB}" \
       -Xmx800m -Xms800m \
       -Dctl=$CONTROL_FILE \
       -XX:ErrorFile=${HERE}/../../hs_err.log \
       -XX:OnError="${HERE}/../../dd_crash_uploader.sh %p" \
       -jar /var/lib/benchmarks/renaissance.jar akka-uct -t 30

  RC=$?
  echo "RC=$RC"

  if [ $RC -ne 0 ]; then
    echo "FAIL:Benchmark crashed" >&2
    exit 1
  fi
done
