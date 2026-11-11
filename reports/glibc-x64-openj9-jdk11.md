---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:28:41 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 53-75 cores)</summary>

```
1794392564 54
1794392569 75
1794392574 75
1794392580 75
1794392585 75
1794392590 75
1794392595 55
1794392600 55
1794392605 55
1794392610 55
1794392615 53
1794392620 53
1794392625 53
1794392630 53
1794392635 53
1794392640 53
1794392645 53
1794392650 53
1794392655 53
1794392660 53
```
</details>

---

