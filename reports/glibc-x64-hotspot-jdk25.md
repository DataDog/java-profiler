---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 07:53:26 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 900 |
| Sample Rate | 15.00/sec |
| Health Score | 938% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770122785 30
1770122790 30
1770122795 32
1770122800 32
1770122805 32
1770122810 32
1770122815 32
1770122820 32
1770122825 32
1770122830 32
1770122835 32
1770122840 32
1770122845 32
1770122850 32
1770122855 32
1770122860 32
1770122865 32
1770122870 32
1770122875 32
1770122880 32
```
</details>

---

