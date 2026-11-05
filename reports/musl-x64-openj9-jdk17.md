---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 19:07:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 85-96 cores)</summary>

```
1793836913 96
1793836918 96
1793836923 96
1793836928 96
1793836933 96
1793836938 96
1793836943 96
1793836948 94
1793836953 94
1793836958 94
1793836963 94
1793836968 94
1793836973 85
1793836978 85
1793836983 85
1793836988 85
1793836993 87
1793836998 87
1793837003 87
1793837008 87
```
</details>

---

