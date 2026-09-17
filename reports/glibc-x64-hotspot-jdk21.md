---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 06:53:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 10-30 cores)</summary>

```
1789642140 12
1789642145 12
1789642150 12
1789642155 10
1789642160 10
1789642165 10
1789642170 10
1789642175 10
1789642180 10
1789642185 10
1789642190 10
1789642195 10
1789642200 30
1789642205 30
1789642210 30
1789642215 30
1789642220 30
1789642225 30
1789642230 30
1789642235 30
```
</details>

---

