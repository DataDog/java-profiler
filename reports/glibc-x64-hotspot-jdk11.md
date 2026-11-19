---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:48:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 935 |
| Sample Rate | 15.58/sec |
| Health Score | 974% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 64-79 cores)</summary>

```
1795095775 64
1795095780 64
1795095785 67
1795095790 67
1795095795 67
1795095800 67
1795095805 67
1795095810 67
1795095815 79
1795095820 79
1795095825 79
1795095830 79
1795095835 79
1795095840 77
1795095845 77
1795095850 77
1795095855 77
1795095860 77
1795095865 77
1795095870 77
```
</details>

---

