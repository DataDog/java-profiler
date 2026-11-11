---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:00:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1794354982 92
1794354987 92
1794354992 92
1794354997 92
1794355002 92
1794355007 92
1794355012 90
1794355017 90
1794355022 88
1794355027 88
1794355032 88
1794355037 88
1794355042 88
1794355047 88
1794355052 88
1794355057 88
1794355062 88
1794355067 88
1794355072 88
1794355077 90
```
</details>

---

