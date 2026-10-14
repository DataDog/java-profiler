---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 12:40:10 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (6 unique values: 83-94 cores)</summary>

```
1791995680 89
1791995685 94
1791995690 94
1791995695 94
1791995700 94
1791995705 94
1791995710 94
1791995715 92
1791995720 92
1791995726 92
1791995731 92
1791995736 88
1791995741 88
1791995746 88
1791995751 88
1791995756 88
1791995761 88
1791995766 83
1791995771 83
1791995776 83
```
</details>

---

