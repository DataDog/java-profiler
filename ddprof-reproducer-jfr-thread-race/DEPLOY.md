# Deployment Guide

This guide shows how to deploy and run the JFR thread race reproducer on a remote machine.

## Prerequisites on Target Machine

- Java 25.0.1 (amd64) - the version where the crash occurs
- At least 2GB available RAM
- Linux or macOS

## Quick Deployment

### 1. Build Fat JAR

On your development machine:

```bash
cd /path/to/java-profiler
./gradlew :ddprof-reproducer-jfr-thread-race:distJar
```

This creates: `ddprof-reproducer-jfr-thread-race/build/libs/jfr-thread-race-reproducer-1.0-all.jar`

### 2. Copy to Target Machine

```bash
# Copy JAR
scp ddprof-reproducer-jfr-thread-race/build/libs/jfr-thread-race-reproducer-1.0-all.jar \
  user@target-machine:/tmp/

# SSH to target
ssh user@target-machine
```

### 3. Run on Target Machine

```bash
cd /tmp

# Basic run (60 seconds)
java -Xmx2g \
  -XX:ErrorFile=hs_err_reproducer_%p.log \
  -XX:-OmitStackTraceInFastThrow \
  -XX:StartFlightRecording=filename=reproducer.jfr,settings=profile \
  -jar jfr-thread-race-reproducer-1.0-all.jar
```

## Running Multiple Iterations

Create a simple runner script on the target machine:

```bash
cat > run-reproducer.sh << 'EOF'
#!/bin/bash

JAR="jfr-thread-race-reproducer-1.0-all.jar"
ITERATIONS=${1:-5}

for i in $(seq 1 $ITERATIONS); do
  echo "========================================"
  echo "Iteration $i of $ITERATIONS"
  echo "========================================"

  java -Xmx2g \
    -XX:ErrorFile=hs_err_reproducer_%p.log \
    -XX:-OmitStackTraceInFastThrow \
    -XX:StartFlightRecording=filename=reproducer-$i.jfr,settings=profile \
    -jar $JAR \
    --threads 300 --idle-ms 25 --churn-ms 0 --duration-sec 120

  # Check if crash occurred
  if ls hs_err_reproducer_* 1> /dev/null 2>&1; then
    echo ""
    echo "!!! CRASH REPRODUCED in iteration $i !!!"
    echo "Crash dump: $(ls -t hs_err_reproducer_* | head -1)"
    break
  fi

  echo "No crash in iteration $i, continuing..."
  echo ""
  sleep 5
done

echo ""
echo "========================================"
echo "Run complete"
echo "========================================"
echo "JFR recordings: reproducer-*.jfr"
echo "Thread stats: thread-stats.csv"
if ls hs_err_reproducer_* 1> /dev/null 2>&1; then
  echo "Crash dumps: hs_err_reproducer_*"
fi
EOF

chmod +x run-reproducer.sh

# Run 5 iterations
./run-reproducer.sh 5
```

## Collecting Results

After running, collect the generated files:

```bash
# On target machine, create archive
tar czf reproducer-results-$(date +%Y%m%d-%H%M%S).tar.gz \
  hs_err_reproducer_* \
  reproducer-*.jfr \
  thread-stats.csv \
  2>/dev/null

# Copy back to development machine
scp user@target-machine:/tmp/reproducer-results-*.tar.gz ./
```

## Advanced Configuration

### Maximum Aggression

For fastest reproduction attempts:

```bash
java -jar jfr-thread-race-reproducer-1.0-all.jar \
  --threads 500 \
  --min-threads 1 \
  --idle-ms 25 \
  --churn-ms 0 \
  --allocations 20 \
  --alloc-size 200000 \
  --duration-sec 300
```

### Steady State Load

For longer-running stable load:

```bash
java -jar jfr-thread-race-reproducer-1.0-all.jar \
  --threads 200 \
  --min-threads 10 \
  --idle-ms 100 \
  --churn-ms 2 \
  --duration-sec 3600
```

### Custom Profiler Configuration

```bash
java -jar jfr-thread-race-reproducer-1.0-all.jar \
  --profiler-config "start,event=cpu,alloc,memory=512k:a"
```

## Monitoring

While the reproducer is running, you can monitor it from another terminal:

```bash
# Find PID
jps | grep jfr-thread-race

# Monitor thread count
watch -n 1 "jcmd <PID> Thread.print | grep 'reproducer-' | wc -l"

# Check JFR status
jcmd <PID> JFR.check

# Monitor CPU and memory
top -p <PID>
```

## Troubleshooting

### "Cannot find native library"

The native library is bundled in the JAR. If you see this error, ensure you're using Java 8+ and the JAR was built correctly.

### "Out of memory"

Reduce thread count or increase heap:

```bash
java -Xmx4g -jar jfr-thread-race-reproducer-1.0-all.jar --threads 150
```

### No TEST_LOG Output

TEST_LOG is only available when using the debug build of ddprof-lib. The fat JAR includes the debug build by default.

## Docker Deployment

To run in a container:

```dockerfile
FROM openjdk:25.0.1-jdk

WORKDIR /app
COPY jfr-thread-race-reproducer-1.0-all.jar .

CMD ["java", "-Xmx2g", \
     "-XX:ErrorFile=/output/hs_err_reproducer_%p.log", \
     "-XX:-OmitStackTraceInFastThrow", \
     "-XX:StartFlightRecording=filename=/output/reproducer.jfr,settings=profile", \
     "-jar", "jfr-thread-race-reproducer-1.0-all.jar"]
```

Run with:

```bash
docker build -t jfr-reproducer .
docker run -v $(pwd)/output:/output jfr-reproducer
```

## What to Look For

### Success Indicators

1. **Crash occurred** - `hs_err_reproducer_*.log` file exists
2. **High thread churn** - Statistics show >500 tasks/sec
3. **Short init windows** - `thread-stats.csv` shows many threads <20μs

### Sending Results

When reporting results, include:

1. Crash dump (`hs_err_reproducer_*.log`)
2. JFR recording (`reproducer.jfr`)
3. Thread statistics (`thread-stats.csv`)
4. Console output showing TEST_LOG traces
5. System info: `uname -a`, `java -version`
