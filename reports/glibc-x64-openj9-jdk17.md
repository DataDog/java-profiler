---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:58:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 68-93 cores)</summary>

```
1793728357 70
1793728362 68
1793728367 68
1793728372 89
1793728377 89
1793728382 89
1793728387 89
1793728393 91
1793728398 91
1793728403 91
1793728408 91
1793728413 91
1793728418 91
1793728423 91
1793728428 91
1793728433 91
1793728438 91
1793728443 93
1793728448 93
1793728453 93
```
</details>

---

