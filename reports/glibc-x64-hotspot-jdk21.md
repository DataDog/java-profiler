---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-09 07:06:59 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 35-41 cores)</summary>

```
1791543738 38
1791543743 38
1791543748 38
1791543753 38
1791543758 39
1791543763 39
1791543768 39
1791543773 39
1791543778 39
1791543783 39
1791543788 39
1791543793 39
1791543798 41
1791543803 41
1791543808 35
1791543813 35
1791543818 35
1791543823 35
1791543828 35
1791543833 35
```
</details>

---

