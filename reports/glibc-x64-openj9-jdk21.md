---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 13:10:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1792688670 51
1792688675 51
1792688680 51
1792688685 53
1792688690 53
1792688695 53
1792688700 53
1792688705 53
1792688710 53
1792688715 53
1792688720 53
1792688725 53
1792688730 53
1792688735 53
1792688740 53
1792688745 53
1792688750 53
1792688755 53
1792688760 53
1792688765 53
```
</details>

---

