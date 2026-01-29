---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 12:19:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 16.30/sec |
| Health Score | 1019% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 23.40/sec |
| Health Score | 1462% |
| Threads | 12 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 58-77 cores)</summary>

```
1769706805 60
1769706810 58
1769706815 58
1769706820 58
1769706825 58
1769706830 60
1769706835 60
1769706840 72
1769706845 72
1769706850 72
1769706855 72
1769706860 72
1769706865 72
1769706870 72
1769706875 72
1769706880 72
1769706885 72
1769706890 72
1769706895 72
1769706900 72
```
</details>

---

