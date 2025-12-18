# Quick Start - Fat JAR Edition

## Build

```bash
./gradlew :ddprof-reproducer-jfr-thread-race:distJar
```

**Output**: `ddprof-reproducer-jfr-thread-race/build/libs/jfr-thread-race-reproducer-1.0-all.jar` (2.9MB)

## Deploy to Remote Machine

```bash
scp ddprof-reproducer-jfr-thread-race/build/libs/jfr-thread-race-reproducer-1.0-all.jar \
  user@remote:/tmp/
```

## Run on Remote Machine

### Basic (60 seconds)
```bash
java -Xmx2g \
  -XX:ErrorFile=hs_err_reproducer_%p.log \
  -XX:-OmitStackTraceInFastThrow \
  -XX:StartFlightRecording=filename=reproducer.jfr,settings=profile \
  -jar jfr-thread-race-reproducer-1.0-all.jar
```

### Maximum Aggression
```bash
java -jar jfr-thread-race-reproducer-1.0-all.jar \
  --threads 500 --idle-ms 25 --churn-ms 0 --duration-sec 300
```

### Help
```bash
java -jar jfr-thread-race-reproducer-1.0-all.jar --help
```

## Output Files

- `ddprof-output.jfr` - Datadog profiler output
- `reproducer.jfr` - JFR recording (from JVM flag)
- `thread-stats.csv` - Thread lifecycle analysis
- `hs_err_reproducer_*.log` - Crash dump (if crash occurs)

## Quick Analysis

```bash
# Check for critical race windows
awk -F',' 'NR>1 && $6 < 20 {print}' thread-stats.csv | wc -l

# Find shortest init windows
awk -F',' 'NR>1 {print $6}' thread-stats.csv | sort -n | head -10
```

## Success Indicators

✅ **Crash occurred** - `hs_err_reproducer_*.log` exists
✅ **High churn** - Console shows >500 tasks/sec
✅ **Critical windows** - 20%+ of threads have <20μs init windows

## All Options

```
--threads <N>           Max threads (default: 200)
--min-threads <N>       Min threads (default: 5)
--churn-ms <N>          Task interval in ms, 0=max (default: 1)
--idle-ms <N>           Thread idle timeout (default: 50)
--allocations <N>       Allocations per task (default: 10)
--alloc-size <N>        Allocation size bytes (default: 100000)
--duration-sec <N>      Run duration (default: 60)
--profiler-config <S>   Profiler config (default: start,event=cpu,alloc,memory=256k:a,file=ddprof-output.jfr)
```
