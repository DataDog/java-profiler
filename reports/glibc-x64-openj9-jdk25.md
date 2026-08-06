---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-06 08:59:59 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 22-30 cores)</summary>

```
1786020955 30
1786020960 30
1786020965 30
1786020970 30
1786020975 30
1786020980 30
1786020985 22
1786020990 22
1786020995 22
1786021000 22
1786021005 22
1786021010 22
1786021015 22
1786021020 22
1786021025 22
1786021030 22
1786021035 22
1786021040 22
1786021045 22
1786021050 22
```
</details>

---

