---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:55:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 68-75 cores)</summary>

```
1794484096 68
1794484101 68
1794484106 68
1794484111 68
1794484116 68
1794484121 68
1794484126 68
1794484131 68
1794484136 68
1794484141 68
1794484146 68
1794484151 68
1794484156 75
1794484161 75
1794484166 75
1794484171 75
1794484176 75
1794484181 75
1794484186 75
1794484191 75
```
</details>

---

