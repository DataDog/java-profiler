---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-07 12:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1791391383 28
1791391388 28
1791391393 28
1791391398 28
1791391403 28
1791391408 28
1791391413 28
1791391418 28
1791391423 28
1791391428 28
1791391433 30
1791391438 30
1791391443 28
1791391448 28
1791391453 28
1791391458 28
1791391463 28
1791391468 28
1791391473 28
1791391478 28
```
</details>

---

