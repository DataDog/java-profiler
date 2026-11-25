---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:08:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 41-47 cores)</summary>

```
1795618872 41
1795618877 41
1795618882 41
1795618887 41
1795618892 41
1795618897 41
1795618902 43
1795618907 43
1795618912 43
1795618917 43
1795618922 43
1795618927 43
1795618932 43
1795618937 43
1795618942 43
1795618947 43
1795618952 43
1795618957 43
1795618962 43
1795618967 43
```
</details>

---

