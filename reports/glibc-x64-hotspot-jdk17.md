---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 12:19:49 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 17.23/sec |
| Health Score | 1077% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 19.03/sec |
| Health Score | 1189% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 41-72 cores)</summary>

```
1769706830 41
1769706835 67
1769706840 67
1769706845 67
1769706850 67
1769706855 67
1769706860 67
1769706865 67
1769706870 67
1769706875 70
1769706880 70
1769706885 70
1769706890 72
1769706895 72
1769706900 72
1769706905 72
1769706910 72
1769706915 72
1769706920 72
1769706925 72
```
</details>

---

