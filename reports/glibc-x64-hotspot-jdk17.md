---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 07:06:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1791543733 24
1791543738 24
1791543743 24
1791543748 24
1791543753 24
1791543758 24
1791543763 24
1791543768 24
1791543773 24
1791543778 24
1791543783 24
1791543788 24
1791543793 24
1791543798 19
1791543803 19
1791543808 19
1791543813 19
1791543818 19
1791543823 19
1791543828 19
```
</details>

---

