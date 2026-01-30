---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-30 05:41:42 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 11 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 820 |
| Sample Rate | 13.67/sec |
| Health Score | 854% |
| Threads | 13 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1769769314 94
1769769319 94
1769769324 94
1769769329 94
1769769334 94
1769769339 94
1769769344 96
1769769349 96
1769769354 96
1769769359 96
1769769364 96
1769769369 96
1769769374 91
1769769380 91
1769769385 91
1769769390 91
1769769395 91
1769769400 91
1769769405 91
1769769410 89
```
</details>

---

