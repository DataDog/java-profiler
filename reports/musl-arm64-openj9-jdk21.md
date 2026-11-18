---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:28:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (4 unique values: 25-36 cores)</summary>

```
1795015347 26
1795015352 26
1795015357 26
1795015362 26
1795015367 26
1795015372 26
1795015377 26
1795015382 26
1795015387 26
1795015392 26
1795015397 26
1795015402 26
1795015407 26
1795015412 26
1795015417 26
1795015422 26
1795015427 26
1795015432 25
1795015437 25
1795015442 36
```
</details>

---

