---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 10:20:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793283342 43
1793283347 48
1793283352 48
1793283357 48
1793283362 48
1793283367 48
1793283372 48
1793283377 48
1793283382 48
1793283387 48
1793283392 48
1793283397 48
1793283402 48
1793283407 48
1793283412 48
1793283417 48
1793283422 48
1793283427 48
1793283432 48
1793283437 43
```
</details>

---

