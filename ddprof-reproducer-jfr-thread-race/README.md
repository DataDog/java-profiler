# JFR Thread Race Reproducer

Standalone application to reproduce a SIGSEGV crash on Java 25.0.1 (amd64) where `Thread::current()` returns nullptr during JFR ObjectAllocationSample event recording.

## Problem Description

The crash occurs during a race condition where:
1. JFR's ObjectAllocationSample attempts to record an allocation event
2. The allocation happens during thread initialization or cleanup
3. JVM's `Thread::current()` returns nullptr (thread not fully initialized or being torn down)
4. JFR attempts to create a stack trace via `JfrStackTraceRepository::record_for_leak_profiler()` without a valid thread context
5. `resource_allocate_bytes()` crashes when dereferencing the nullptr Thread

### Stack Trace
```
V  [libjvm.so+0xf23cf8]  resource_allocate_bytes(unsigned long, AllocFailStrategy::AllocFailEnum)+0x28
V  [libjvm.so+0xaa9811]  JfrStackTrace::JfrStackTrace()+0x21
V  [libjvm.so+0xaac6cc]  JfrStackTraceRepository::record_for_leak_profiler(JavaThread*, int)+0x4c
V  [libjvm.so+0xe54fde]  ObjectSampler::sample(HeapWordImpl**, unsigned long, JavaThread*)+0x25e
V  [libjvm.so+0xa456de]  JfrAllocationTracer::JfrAllocationTracer(Klass const*, HeapWordImpl**, unsigned long, bool, JavaThread*)+0x5e
V  [libjvm.so+0x49351f]  AllocTracer::send_allocation_in_new_tlab(Klass*, HeapWordImpl**, unsigned long, unsigned long, JavaThread*)+0x2f
...
j  org.eclipse.jetty.util.thread.QueuedThreadPool$Runner.run()V
```

## Architecture

The reproducer creates conditions that maximize the chance of hitting this race:

1. **Jetty QueuedThreadPool** - Uses the exact thread pool from production stack traces
2. **Aggressive Thread Churn** - Short-lived threads (50ms idle timeout, immediate shutdown)
3. **Immediate Allocation** - Workers allocate large byte arrays immediately upon thread start
4. **High Task Rate** - Submits 1000+ tasks per second
5. **Native Instrumentation** - TEST_LOG calls track thread initialization and allocation sampling

## Building

```bash
# Build the debug profiler library (required for TEST_LOG)
./gradlew :ddprof-lib:buildDebug

# Build the reproducer
./gradlew :ddprof-reproducer-jfr-thread-race:build
```

## Running

### Basic Execution

```bash
./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer
```

### With Custom Parameters

```bash
./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer --args="--threads 300 --duration-sec 120"
```

### Available Options

```
--threads <N>           Maximum threads in pool (default: 200)
--min-threads <N>       Minimum threads in pool (default: 5)
--churn-ms <N>          Task submission interval in ms (default: 1)
--idle-ms <N>           Thread idle timeout in ms (default: 50)
--allocations <N>       Allocations per task (default: 10)
--alloc-size <N>        Allocation size in bytes (default: 100000)
--duration-sec <N>      Run duration in seconds (default: 60)
--profiler-config <S>   Datadog profiler config (default: start,event=cpu,alloc,memory=256k:a)
```

### Running with Specific Java Version

```bash
JAVA_TEST_HOME=/path/to/java-25.0.1 ./gradlew :ddprof-reproducer-jfr-thread-race:runReproducer
```

## Output Analysis

### Console Output

The reproducer provides real-time statistics:

```
[REPRODUCER] JFR Thread Race Reproducer Starting
[REPRODUCER] Java Version: 25.0.1
[REPRODUCER] Thread Pool: 5-200 threads, 50ms idle timeout
[REPRODUCER] Task submission rate: 1000.0/sec
[REPRODUCER] Profiler started: OK
[TEST::INFO] ProfiledThread::initCurrentThread TID=47234 START
[TEST::INFO] ObjectSampler::recordAllocation TID=47234 SIZE=100000
[TEST::INFO] Profiler::recordJVMTISample TID=47234 TYPE=-12 DEFERRED=0
[REPRODUCER] Statistics (10s): submitted=10000, completed=9847, rate=984.7 tasks/sec, threads=127
```

### Thread Statistics CSV

Location: `build/thread-stats.csv`

Contains timing data for thread initialization windows:

```csv
threadId,threadName,createdAtNanos,firstAllocationAtNanos,initWindowNanos,initWindowMicros,allocationCount
47234,reproducer-47,1234567890123456,1234567890145678,22222,22.222,100
47235,reproducer-48,1234567890125789,1234567890143567,17778,17.778,100
```

**Critical**: Threads with `initWindowMicros < 20` are in the race window where Thread::current() might return nullptr.

### Analysis Summary

The reproducer automatically analyzes init windows:

```
[TRACKER] Thread Init Window Analysis:
[TRACKER]   Threads analyzed: 1247
[TRACKER]   Min: 8.342 μs
[TRACKER]   Max: 452.781 μs
[TRACKER]   Median: 34.567 μs
[TRACKER]   Average: 42.123 μs
[TRACKER]   Critical (<20μs): 347 (27.8%)
```

### JFR Recording

Location: `build/reproducer.jfr`

Contains JFR events including:
- jdk.ObjectAllocationSample
- jdk.ThreadStart
- jdk.ThreadEnd

### Crash Output

If crash occurs: `build/hs_err_reproducer_<pid>.log`

## Native Instrumentation

The reproducer includes TEST_LOG instrumentation in:

### ddprof-lib/src/main/cpp/thread.cpp
- `ProfiledThread::initCurrentThread()` - Tracks Java thread initialization
- `ProfiledThread::current()` - Tracks lazy thread allocation
- `ProfiledThread::currentSignalSafe()` - Tracks signal-safe thread access

### ddprof-lib/src/main/cpp/objectSampler.cpp
- `ObjectSampler::recordAllocation()` - Tracks allocation sampling events

### ddprof-lib/src/main/cpp/profiler.cpp
- `Profiler::recordJVMTISample()` - Tracks JVMTI sample recording

## Tuning for Reproduction

### Strategy 1: Maximum Thread Churn
```bash
--threads 300 --idle-ms 25 --churn-ms 0.5
```

### Strategy 2: Large Allocations (TLAB Overflow)
```bash
--alloc-size 500000 --allocations 20
```

### Strategy 3: Extended Duration
```bash
--duration-sec 300
```

### Strategy 4: Extreme Concurrency
```bash
--threads 500 --min-threads 1 --idle-ms 10
```

## Expected Results

### Primary Goal
Reproduce SIGSEGV crash with stack trace showing:
- `resource_allocate_bytes()`
- `JfrStackTrace::JfrStackTrace()`
- `JfrStackTraceRepository::record_for_leak_profiler()`

### Secondary Goals
1. TEST_LOG output demonstrates thread initialization sequence
2. Thread statistics CSV captures narrow init windows (<20μs)
3. Identify correlation between short init windows and crashes

## Troubleshooting

### "Cannot find debug library"
```bash
./gradlew :ddprof-lib:buildDebug
```

### "Out of memory"
Reduce concurrency:
```bash
--threads 100 --churn-ms 10
```

### "No TEST_LOG output"
Ensure debug build is used. Verify with:
```bash
./gradlew :ddprof-lib:buildDebug --rerun-tasks
```

### "Reproducer completes without crash"
Try more aggressive parameters or longer duration. The race window is narrow and may require multiple runs.

## Files Generated

- `build/reproducer.jfr` - JFR recording
- `build/thread-stats.csv` - Thread lifecycle statistics
- `build/hs_err_reproducer_<pid>.log` - Crash dump (if crash occurs)

## Technical Details

### Thread Lifecycle Race Window

The race occurs during thread initialization when:
1. Jetty creates a new worker thread
2. Thread starts executing AllocationWorker.run()
3. Worker immediately allocates large byte arrays
4. JFR ObjectAllocationSample triggers
5. JVM's Thread::current() may return nullptr if:
   - Thread-local storage not fully initialized
   - Thread cleanup already started
6. JFR stack trace creation crashes on nullptr dereference

The window is typically 10-50 microseconds, making it challenging to reproduce consistently.
