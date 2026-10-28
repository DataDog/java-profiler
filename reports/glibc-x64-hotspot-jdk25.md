---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:01:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 49-73 cores)</summary>

```
1793184734 49
1793184739 49
1793184744 49
1793184749 51
1793184754 51
1793184760 51
1793184765 51
1793184770 51
1793184775 51
1793184780 51
1793184785 51
1793184790 49
1793184795 49
1793184800 49
1793184805 49
1793184810 49
1793184815 49
1793184820 49
1793184825 67
1793184830 67
```
</details>

---

