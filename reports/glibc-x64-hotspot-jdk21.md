---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 59-75 cores)</summary>

```
1793995740 59
1793995745 61
1793995750 61
1793995755 61
1793995760 61
1793995765 61
1793995770 61
1793995775 61
1793995780 61
1793995785 61
1793995790 59
1793995795 59
1793995800 59
1793995805 59
1793995810 59
1793995815 59
1793995820 59
1793995825 59
1793995830 59
1793995835 59
```
</details>

---

