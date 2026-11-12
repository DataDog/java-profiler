---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:58:58 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 28-32 cores)</summary>

```
1794480740 29
1794480745 29
1794480750 32
1794480755 32
1794480760 32
1794480765 32
1794480770 30
1794480775 30
1794480780 30
1794480785 30
1794480790 30
1794480795 30
1794480800 30
1794480805 30
1794480810 30
1794480815 30
1794480820 30
1794480825 30
1794480830 30
1794480835 30
```
</details>

---

