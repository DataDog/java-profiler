---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 13:19:33 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 909 |
| Sample Rate | 15.15/sec |
| Health Score | 947% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 84-93 cores)</summary>

```
1794420775 89
1794420780 89
1794420785 89
1794420790 89
1794420795 89
1794420800 89
1794420805 89
1794420810 89
1794420815 89
1794420820 93
1794420825 93
1794420830 84
1794420835 84
1794420840 84
1794420845 84
1794420850 84
1794420855 84
1794420860 84
1794420865 84
1794420870 84
```
</details>

---

