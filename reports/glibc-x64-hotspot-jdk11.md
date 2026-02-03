---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 07:53:25 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (5 unique values: 66-72 cores)</summary>

```
1770122795 66
1770122800 66
1770122805 68
1770122810 68
1770122815 68
1770122820 68
1770122825 68
1770122830 68
1770122835 68
1770122840 68
1770122845 68
1770122850 66
1770122855 66
1770122860 70
1770122865 70
1770122870 72
1770122875 72
1770122880 72
1770122885 72
1770122890 72
```
</details>

---

