#!/bin/bash

# Install SDKMAN and JDK
export SDKMAN_DIR="/usr/local/sdkman" && curl -s "https://get.sdkman.io" | bash
source /usr/local/sdkman/bin/sdkman-init.sh
sdk install java 11.0.28-tem

export JAVA_HOME=`sdk home java 11.0.28-tem`

function usage() {
    echo "./run_benchmark.sh --iterations <iterations> (default 10) --version <version> --output <output_file> --modes <mode_list> (default 'cpu,wall') --config [candidate|baseline]"
    echo "Modes are encoded as comma separated list of modes. Supported modes are: cpu, wall and alloc"
}

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ITERATIONS=5
MODES="cpu,wall"
while [ $# -gt 0 ]; do
  case "$1" in
    "--iterations") ITERATIONS=$2; shift; shift;;
    "--version") VERSION=$2; shift; shift;;
    "--output") JSON_OUTPUT=$2; shift; shift;;
    "--modes") MODES=$2; shift; shift;;
    "--config") CONFIG=$2; shift; shift;;
    "--help")
        usage
        exit 0
        ;;
    *) usage; exit 1;;
  esac
done

if [ -z "$VERSION" ] || [ -z "$JSON_OUTPUT" ] || [ -z "$CONFIG" ]; then
    usage
    exit 1
fi

JFR_DIR="${ARTIFACTS_DIR}/jfr"
TXT_OUTPUT="$JSON_OUTPUT.txt"

mkdir -p $JFR_DIR

CPU="off"
WALL="off"
ALLOC="off"
MEMLEAK="off"
for MODE in ${MODES//,/$IFS}; do
    if [ "$MODE" == "cpu" ]; then
        CPU_ARG="cpu=10m"
        CPU="on"
    elif [ "$MODE" == "wall" ]; then
        WALL_ARG="wall=10m"
        WALL="on"
    elif [ "$MODE" == "alloc" ]; then
        ALLOC_ARG="alloc=262144"
        ALLOC="on"
    elif [ "$MODE" == "memleak" ]; then
        MEMLEAK_ARG="memleak=262144"
        MEMLEAK="on"
    fi
done

mvn org.apache.maven.plugins:maven-dependency-plugin:2.1:get \
    -DrepoUrl=https://central.sonatype.com/repository/maven-snapshots/ \
    -Dartifact=com.datadoghq:ddprof:$VERSION

mkdir -p /var/lib/datadog/$VERSION
rm -rf /var/lib/datadog/$VERSION/*


# The directory contains platform specific profiling library 
ARCH=`uname -m`
ARCH_DIR=""
if [ "$ARCH" == "x86_64" ]; then
  ARCH_DIR=linux-x64
elif [ "$ARCH" == "aarch64" ]; then
  ARCH_DIR=linux-arm64
fi

unzip -q -d /var/lib/datadog/$VERSION /root/.m2/repository/com/datadoghq/ddprof/$VERSION/ddprof-$VERSION.jar
AGENT_LIB=$(find /var/lib/datadog/$VERSION -name 'libjavaProfiler.so' | fgrep ${ARCH_DIR}/)

ls -la /var/lib/datadog/$VERSION/*
echo $AGENT_LIB

JAVA_VERSION=$(cat $JAVA_HOME/release | fgrep 'JAVA_VERSION=' | cut -f2 -d'=')
if [ -z "$JAVA_VERSION" ]; then
    JAVA_VERSION=$(cat $JAVA_HOME/release | fgrep 'JVM_VERSION=' | cut -f2 -d'=')
fi

for test_item in 'dotty|-r 10' 'finagle-http|-r 4' 'finagle-chirper|-r 4' 'page-rank|-r 3' 'future-genetic|-r 5' 'akka-uct|-r 2' 'movie-lens|-r 3' 'scala-doku|-r 4' 'chi-square|-r 6' 'fj-kmeans|-r 15' 'dec-tree|-r 15' 'naive-bayes|-r 15' 'als|-r 10' 'par-mnemonics|-r 5' 'scala-kmeans|-r 60' 'philosophers|-r 2' 'log-regression|-r 30' 'gauss-mix|-r 8' 'mnemonics|-r 4' ; do
    test=$(echo $test_item | cut -f1 -d'|')
    param=$(echo $test_item | cut -f2 -d'|')

    echo "==== renaissance:$test (cpu=$CPU, wall=$WALL, alloc=$ALLOC, memleak=$MEMLEAK)" | tee -a $TXT_OUTPUT
    echo "==   config: $CONFIG" | tee -a $TXT_OUTPUT
    echo "==   ddprof: $VERSION" | tee -a $TXT_OUTPUT
    echo "==   java: $JAVA_VERSION" | tee -a $TXT_OUTPUT

    chmod a+x "${HERE}"/mem_watch.sh
    for i in $( seq 1 $ITERATIONS ); do
        if [ ! -z "$MODES" ]; then
            AGENT_ARG="-agentpath:${AGENT_LIB}=start,jfr=7,file=${JFR_DIR}/${CONFIG}_${test}_${i}.jfr,jstackdepth=512,cstack=dwarf,safemode=0,$CPU_ARG,$WALL_ARG,$ALLOC_ARG,$MEMLEAK_ARG"
        fi

        CONTROL_FILE=".running_${CONFIG}_${test}_${i}"
        touch $CONTROL_FILE
       "${HERE}"/mem_watch.sh $CONTROL_FILE $TXT_OUTPUT &
        TIME=$(/usr/bin/time -f "# %e" java -Xms1g -Xmx1g -XX:+AlwaysPreTouch -Dctl=$CONTROL_FILE $AGENT_ARG -jar /var/lib/benchmarks/renaissance.jar $test $param 2>&1 | fgrep '#' | cut -f2 -d' ')
        rm -f $CONTROL_FILE

        echo "time: $TIME" | tee -a $TXT_OUTPUT
    done
done

benchmark_analyzer convert \
  --framework=JavaProfilerRenaissance \
  --extra_params="{\"iterations\": \"${ITERATIONS}\", \"modes\": \"${MODES}\"}" \
  --outpath="$JSON_OUTPUT" \
  $TXT_OUTPUT
