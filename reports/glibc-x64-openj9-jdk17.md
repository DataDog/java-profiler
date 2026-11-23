---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:28:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (6 unique values: 51-72 cores)</summary>

```
1795429418 70
1795429423 70
1795429428 70
1795429433 70
1795429438 72
1795429443 72
1795429448 72
1795429453 53
1795429458 53
1795429463 53
1795429468 53
1795429473 53
1795429478 53
1795429483 53
1795429488 55
1795429493 55
1795429498 55
1795429503 55
1795429508 57
1795429513 57
```
</details>

---

