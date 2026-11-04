---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 05:47:33 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 39-60 cores)</summary>

```
1793788913 60
1793788918 60
1793788923 39
1793788928 39
1793788933 39
1793788938 39
1793788943 39
1793788948 39
1793788953 39
1793788958 39
1793788963 39
1793788968 39
1793788973 39
1793788978 39
1793788983 39
1793788988 39
1793788993 39
1793788998 39
1793789003 39
1793789008 39
```
</details>

---

