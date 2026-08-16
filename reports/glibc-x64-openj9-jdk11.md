---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-16 05:46:46 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 878 |
| Sample Rate | 14.63/sec |
| Health Score | 914% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1786873395 79
1786873400 79
1786873405 79
1786873410 79
1786873415 81
1786873420 81
1786873425 81
1786873430 81
1786873435 81
1786873440 81
1786873445 81
1786873450 81
1786873455 81
1786873460 81
1786873465 81
1786873470 81
1786873475 81
1786873480 81
1786873485 81
1786873490 81
```
</details>

---

