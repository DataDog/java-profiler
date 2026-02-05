---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-05 04:29:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 11 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 927 |
| Sample Rate | 15.45/sec |
| Health Score | 966% |
| Threads | 12 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (5 unique values: 37-47 cores)</summary>

```
1770283423 37
1770283428 39
1770283433 39
1770283438 39
1770283443 39
1770283448 37
1770283453 37
1770283458 37
1770283463 37
1770283468 37
1770283473 37
1770283478 37
1770283483 37
1770283488 39
1770283493 39
1770283498 43
1770283503 43
1770283508 43
1770283513 43
1770283518 43
```
</details>

---

