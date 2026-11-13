---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 08:23:06 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794575899 32
1794575904 32
1794575909 32
1794575914 32
1794575919 32
1794575924 32
1794575929 32
1794575934 32
1794575939 32
1794575944 32
1794575949 32
1794575954 32
1794575959 32
1794575964 32
1794575969 32
1794575974 32
1794575979 32
1794575984 32
1794575989 32
1794575994 32
```
</details>

---

