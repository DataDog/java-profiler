# Quick Start Guide

## Prerequisites

- Java 25.0.1 (amd64) - the version where the crash occurs
- Gradle 8.x

## Quick Run

```bash
# 1. Build everything
./gradlew :ddprof-reproducer-jfr-thread-race:build

# 2. Run with default settings (60 seconds)
./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer

# 3. Check results
cat ddprof-reproducer-jfr-thread-race/build/thread-stats.csv
```

## Running Multiple Iterations

```bash
# Run 5 times with 2-minute duration each
for i in {1..5}; do
  echo "=== Iteration $i ==="
  JAVA_TEST_HOME=/path/to/java-25.0.1 \
    ./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer \
    --args="--duration-sec 120 --threads 300"

  # Check if crash occurred
  if ls ddprof-reproducer-jfr-thread-race/build/hs_err_* 1> /dev/null 2>&1; then
    echo "CRASH REPRODUCED in iteration $i!"
    break
  fi

  # Small delay between iterations
  sleep 5
done
```

## Analyzing Results

### Check Thread Init Windows

```bash
# Find threads with critical race windows (<20μs)
awk -F',' 'NR>1 && $6 < 20 { print $0 }' \
  ddprof-reproducer-jfr-thread-race/build/thread-stats.csv | \
  sort -t',' -k6 -n | head -20
```

### Grep TEST_LOG Output

When running, pipe output to a file to analyze TEST_LOG traces:

```bash
./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer 2>&1 | \
  tee reproducer.log

# Filter for specific thread
grep "TID=47234" reproducer.log

# Look for allocation patterns
grep "ObjectSampler::recordAllocation" reproducer.log | head -100
```

### Analyze JFR Recording

```bash
# Using jfr command-line tool (Java 11+)
jfr print --events jdk.ObjectAllocationSample \
  ddprof-reproducer-jfr-thread-race/build/reproducer.jfr | head -100

# Or open in JDK Mission Control
jmc ddprof-reproducer-jfr-thread-race/build/reproducer.jfr
```

## Common Scenarios

### Scenario 1: Maximum Aggression

Try to hit the crash as quickly as possible:

```bash
./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer --args="\
  --threads 500 \
  --min-threads 1 \
  --idle-ms 25 \
  --churn-ms 0.5 \
  --allocations 20 \
  --alloc-size 200000 \
  --duration-sec 300"
```

### Scenario 2: Steady State Load

Maintain high but sustainable load:

```bash
./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer --args="\
  --threads 200 \
  --min-threads 10 \
  --idle-ms 100 \
  --churn-ms 2 \
  --duration-sec 600"
```

### Scenario 3: TLAB Overflow Focus

Force allocations outside TLAB:

```bash
./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer --args="\
  --alloc-size 1000000 \
  --allocations 10 \
  --threads 150"
```

## Debugging Tips

### Enable More Verbose Output

Modify the JVM args in build.gradle:

```gradle
jvmArgs = [
  '-Xmx2g',
  '-XX:ErrorFile=build/hs_err_reproducer_%p.log',
  '-XX:-OmitStackTraceInFastThrow',
  '-XX:StartFlightRecording=filename=build/reproducer.jfr,settings=profile',
  '-Xlog:jfr=debug,thread=debug'  // Add this
]
```

### Monitor with jcmd

In another terminal while reproducer is running:

```bash
# Find PID
jps | grep JfrThreadRaceReproducer

# Monitor thread state
watch -n 1 "jcmd <PID> Thread.print | grep 'reproducer-' | wc -l"

# Check JFR status
jcmd <PID> JFR.check
```

### Collect System Metrics

```bash
# Monitor system load while reproducing
dstat -tcm 1 > system-metrics.log &
DSTAT_PID=$!

./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer

kill $DSTAT_PID
```

## Interpreting Results

### Success Indicators

1. **Crash Occurred**
   - File `build/hs_err_reproducer_*.log` exists
   - Stack trace contains `resource_allocate_bytes()` and `JfrStackTrace::JfrStackTrace()`

2. **Near-Miss (High Probability)**
   - 20%+ of threads have init windows <20μs
   - TEST_LOG shows rapid thread initialization
   - High task completion rate (>500/sec)

3. **Not Optimal**
   - Very few threads <20μs init window
   - Low thread churn
   - Need to increase aggression parameters

### Example Good Output

```
[TRACKER] Thread Init Window Analysis:
[TRACKER]   Threads analyzed: 2847
[TRACKER]   Min: 6.123 μs          <- Very good!
[TRACKER]   Median: 18.456 μs      <- Good!
[TRACKER]   Critical (<20μs): 1247 (43.8%)  <- Excellent!
```

### Example Poor Output

```
[TRACKER] Thread Init Window Analysis:
[TRACKER]   Threads analyzed: 147
[TRACKER]   Min: 85.234 μs         <- Too slow
[TRACKER]   Median: 142.567 μs     <- Way too slow
[TRACKER]   Critical (<20μs): 3 (2.0%)  <- Not hitting race window
```

In the poor case, increase thread churn and reduce idle timeout.

## Next Steps After Crash

1. **Preserve Evidence**
   ```bash
   cp build/hs_err_reproducer_*.log crash-$(date +%Y%m%d-%H%M%S).log
   cp build/reproducer.jfr crash-$(date +%Y%m%d-%H%M%S).jfr
   cp build/thread-stats.csv thread-stats-$(date +%Y%m%d-%H%M%S).csv
   ```

2. **Analyze Stack Trace**
   ```bash
   grep -A 50 "Stack:" crash-*.log
   ```

3. **Correlate with TEST_LOG**
   - Look for the thread ID in the crash
   - Find corresponding TEST_LOG entries
   - Identify exact sequence of events

4. **Add More Instrumentation**
   - Based on findings, add more TEST_LOG calls
   - Rebuild with `./gradlew :ddprof-lib:buildDebug`
   - Re-run reproducer
