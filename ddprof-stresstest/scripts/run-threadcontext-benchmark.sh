#!/bin/bash
# Run ThreadContext performance benchmark
# Compares JNI-based vs DirectByteBuffer-based implementations

set -e

JAVA_TEST_HOME="${JAVA_TEST_HOME:-$JAVA_HOME}"

echo "Building JMH benchmark JAR..."
./gradlew :ddprof-stresstest:jmhJar

echo ""
echo "Running ThreadContext benchmark..."
echo "This will take several minutes as it runs multiple configurations with 1, 2, 4, 8, and 16 threads"
echo ""

# Run the benchmark with specific pattern to match our ThreadContext tests
"${JAVA_TEST_HOME}/bin/java" -jar ddprof-stresstest/build/libs/stresstests.jar \
    "ThreadContextBenchmark.*" \
    -rf json \
    -rff build/threadcontext-benchmark-results.json

echo ""
echo "Benchmark complete!"
echo "Results saved to: build/threadcontext-benchmark-results.json"

