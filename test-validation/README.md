# JFR Validation

This directory contains JFR (Java Flight Recorder) validation scripts for profiler integration tests.

## Overview

The validation system uses [jfr-shell](https://github.com/btraceio/jfr-shell) to perform deep inspection of JFR recordings, verifying that the profiler is collecting expected events with correct data.

## Files

### validate-jfr.jfrs

Main JFR validation script that performs comprehensive event analysis.

**Usage**:
```bash
jbang jfr-shell@btraceio script validate-jfr.jfrs \
  <recording.jfr> \
  <scenario> \
  [threshold_multiplier]
```

**Arguments**:
- `recording.jfr` - Path to JFR recording file
- `scenario` - Test scenario (`profiler-only` or `tracer+profiler`)
- `threshold_multiplier` - Optional multiplier for thresholds (default: 1.0)

**Example**:
```bash
# Validate profiler-only recording with default thresholds
jbang jfr-shell@btraceio script validate-jfr.jfrs \
  profiler-only.jfr \
  profiler-only \
  1.0

# Validate with adjusted thresholds for OpenJ9
jbang jfr-shell@btraceio script validate-jfr.jfrs \
  recording.jfr \
  profiler-only \
  0.5
```

**Exit codes**:
- `0` - All validations passed
- `1` - Validation failed (with specific error message)
- `2` - JFR file cannot be opened

### thresholds.env

Configuration file defining minimum event count thresholds.

**Base thresholds** (30-second recording, HotSpot, x64-glibc):
- `BASE_EXECUTION_SAMPLES=100` - Minimum ExecutionSample events
- `BASE_ALLOCATIONS=500` - Minimum ObjectAllocationSample events
- `BASE_THREAD_COUNT=4` - Minimum unique threads sampled

**Platform multipliers**:
- `THRESHOLD_X64_GLIBC=1.0` - x64 with glibc (baseline)
- `THRESHOLD_X64_MUSL=1.0` - x64 with musl (Alpine)
- `THRESHOLD_ARM64_GLIBC=0.8` - ARM64 with glibc
- `THRESHOLD_ARM64_MUSL=0.8` - ARM64 with musl

**JVM type multipliers**:
- `THRESHOLD_HOTSPOT=1.0` - HotSpot JVM (baseline)
- `THRESHOLD_OPENJ9=0.5` - OpenJ9 JVM (produces fewer samples)

**Threshold calculation**:
```
final_threshold = base_threshold × platform_mult × jvm_mult
```

## Validation Categories

### 1. ExecutionSample Events (CPU Profiling)

**What it validates**:
- Minimum event count (≥100 for 30s recording)
- Events are present and parseable

**Why it matters**:
- Verifies CPU profiling is working
- Ensures sampling rate is sufficient

**Failure scenarios**:
- Profiler not started
- Native library failed to load
- Sampling configuration incorrect

### 2. Stack Traces

**What it validates**:
- Stack traces present in ExecutionSample events
- Minimum 95% of samples have valid stack traces

**Why it matters**:
- Stack traces are essential for identifying hot code paths
- Missing stack traces indicate profiler integration issues

**Failure scenarios**:
- Async profiler integration broken
- JVM internal issues
- Stack unwinding failures

### 3. Thread Diversity

**What it validates**:
- Multiple unique threads are sampled (≥4 threads)
- Thread names are captured correctly

**Why it matters**:
- Verifies profiler samples across all active threads
- Ensures multi-threaded applications are profiled correctly

**Failure scenarios**:
- Thread sampling configuration incorrect
- Single-threaded profiling only
- Thread metadata not captured

### 4. ObjectAllocationSample Events

**What it validates**:
- Minimum event count (≥500 for 30s recording)
- Allocation types are captured

**Why it matters**:
- Verifies allocation profiling is working
- Ensures memory profiling data is collected

**Failure scenarios**:
- Allocation profiling disabled
- TLAB events not configured
- Sampling threshold too high

### 5. ThreadAllocationStatistics Events

**What it validates**:
- Per-thread allocation statistics present
- Events contain valid data

**Why it matters**:
- Provides per-thread allocation totals
- Useful for identifying allocation-heavy threads

**Note**: This event type is optional and may not be available on all JDK versions.

### 6. Scenario-Specific Validation

**profiler-only**:
- Validates profiler operates correctly without tracing
- Baseline profiler functionality test

**tracer+profiler**:
- Validates profiler operates correctly with tracing enabled
- Future: will validate span context propagation in JFR events

## Threshold Tuning

Thresholds are conservative starting points. They should be tuned based on actual CI run data.

### Tuning Process

1. **Collect baseline data**:
   ```bash
   # Run tests and collect event counts
   for recording in *.jfr; do
     jbang jfr-shell@btraceio show $recording "events/jdk.ExecutionSample | count()"
   done
   ```

2. **Calculate P5 (5th percentile)**:
   - Sort event counts from all successful runs
   - Find 5th percentile value (95% of runs exceed this)

3. **Set threshold**:
   ```
   threshold = P5 × 0.8  # 80% of P5 provides safety margin
   ```

4. **Update thresholds.env**:
   ```bash
   # For platform with P5 = 125 ExecutionSample events
   THRESHOLD_ARM64_GLIBC=0.8  # 100 × 0.8 = 80 events minimum
   ```

5. **Monitor and iterate**:
   - Track false positive/negative rates
   - Adjust multipliers as needed
   - Document changes in thresholds.env

### Platform-Specific Considerations

**ARM64 platforms** (0.8× multiplier):
- Lower sampling rates due to hardware characteristics
- JIT compiler differences
- Conservative threshold provides stability

**OpenJ9 JVM** (0.5× multiplier):
- Different JIT compilation strategy
- Typically produces 50% fewer samples than HotSpot
- This is expected behavior, not a bug

**Alpine Linux** (musl):
- Same thresholds as glibc for same architecture
- Musl libc has minimal impact on profiling

## Troubleshooting

### Validation Fails: Insufficient ExecutionSample Events

**Problem**: `ERROR: Insufficient ExecutionSample events`

**Diagnostic steps**:
1. Check JFR file size: `ls -lh recording.jfr`
   - Should be >1MB for 30s recording
   - If <100KB, profiler likely not started

2. Inspect JFR manually:
   ```bash
   jbang jfr-shell@btraceio show recording.jfr "events/jdk.ExecutionSample | count()"
   ```

3. Check agent logs for errors:
   ```bash
   grep -i "error\|exception" agent.log
   ```

**Possible causes**:
- Profiler not enabled: Check `-Ddd.profiling.enabled=true`
- Native library not loaded: Check for libjavaProfiler.so errors
- Short test duration: Ensure test runs for at least 30 seconds
- Platform-specific: May need to adjust threshold multiplier

### Validation Fails: Missing Stack Traces

**Problem**: `ERROR: Missing stack traces in ExecutionSample events`

**Diagnostic steps**:
1. Check if any samples have stack traces:
   ```bash
   jbang jfr-shell@btraceio show recording.jfr \
     "events/jdk.ExecutionSample[exists(stackTrace)] | count()"
   ```

2. Compare to total samples:
   ```bash
   jbang jfr-shell@btraceio show recording.jfr \
     "events/jdk.ExecutionSample | count()"
   ```

**Possible causes**:
- Async profiler integration issue
- JVM internal stack unwinding failure
- Profiler configuration error

### Validation Fails: Insufficient Thread Diversity

**Problem**: `ERROR: Insufficient thread diversity`

**Diagnostic steps**:
1. List sampled threads:
   ```bash
   jbang jfr-shell@btraceio show recording.jfr \
     "events/jdk.ExecutionSample | groupBy(sampledThread/javaName)"
   ```

2. Check test app thread creation:
   - Ensure test app actually creates multiple threads
   - Verify threads are doing work (not blocked)

**Possible causes**:
- Test app not creating threads
- Threads blocked/sleeping
- Single-threaded profiling configuration

### jbang Not Found

**Problem**: `jbang: command not found`

**Solution**: Install jbang:
```bash
curl -Ls https://sh.jbang.dev | bash -s - app setup
export PATH="$HOME/.jbang/bin:$PATH"
```

Or use the prerequisite installation script:
```bash
./.gitlab/dd-trace-integration/install-prerequisites.sh
```

## Integration with CI

The validation scripts are automatically run in the GitLab CI pipeline:

```yaml
script:
  # Run test
  - java -javaagent:dd-java-agent.jar \
      -Ddd.profiling.jfr-template-override-file=recording.jfr \
      ProfilerTestApp --duration 30

  # Validate JFR recording
  - jbang jfr-shell@btraceio script \
      test-validation/validate-jfr.jfrs \
      recording.jfr \
      profiler-only \
      ${THRESHOLD_MULTIPLIER}
```

See `.gitlab/dd-trace-integration/run-integration-test.sh` for the complete implementation.

## Advanced Usage

### Custom Validation Scripts

Create custom validation scripts for specific scenarios:

```bash
#!/usr/bin/env jbang jfr-shell@btraceio script

# custom-validation.jfrs
open $1

# Custom validation logic
set my_events = events/my.custom.Event | count()
if ${my_events.count} < 10
  echo "ERROR: Not enough custom events"
  exit 1
endif

echo "SUCCESS"
close
```

### JSON Output for Programmatic Processing

```bash
jbang jfr-shell@btraceio show recording.jfr \
  "events/jdk.ExecutionSample | groupBy(sampledThread/javaName) | top(10, by=count)" \
  --format json > thread-samples.json
```

### Correlation Analysis

```bash
#!/usr/bin/env jbang jfr-shell@btraceio script

# Correlate allocations with GC events
open $1

show events/jdk.ObjectAllocationSample | \
  decorateByTime(events/jdk.GarbageCollection, -100ms, +100ms) | \
  groupBy(objectClass/name) | \
  top(20, by=sum(weight))

close
```

## Related Documentation

- [Test Applications README](../test-apps/README.md) - Test workload documentation
- [jfr-shell Documentation](https://github.com/btraceio/jfr-shell) - JFR-shell user guide
- [JFR Event Reference](https://sap.github.io/SapMachine/jfrevents/) - JDK JFR events
- [Integration Tests CI](./.gitlab/dd-trace-integration/.gitlab-ci.yml) - CI configuration
