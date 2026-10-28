---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:43:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1793187381 61
1793187386 61
1793187391 61
1793187396 61
1793187401 63
1793187406 63
1793187411 63
1793187416 63
1793187421 63
1793187426 63
1793187431 63
1793187436 63
1793187441 63
1793187446 63
1793187451 63
1793187456 63
1793187461 63
1793187466 63
1793187471 63
1793187476 63
```
</details>

---

