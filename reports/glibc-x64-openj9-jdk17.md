---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 58-65 cores)</summary>

```
1790172165 60
1790172170 60
1790172175 60
1790172180 60
1790172185 58
1790172190 58
1790172195 60
1790172200 60
1790172205 63
1790172210 63
1790172215 63
1790172220 63
1790172225 63
1790172230 65
1790172235 65
1790172240 65
1790172245 65
1790172250 65
1790172255 65
1790172260 65
```
</details>

---

