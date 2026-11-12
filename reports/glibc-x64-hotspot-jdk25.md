---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:58:58 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1794480790 28
1794480795 28
1794480800 28
1794480805 28
1794480810 30
1794480815 30
1794480820 30
1794480825 30
1794480830 30
1794480835 30
1794480840 30
1794480845 30
1794480850 30
1794480855 30
1794480860 32
1794480865 32
1794480870 32
1794480875 32
1794480880 32
1794480885 32
```
</details>

---

