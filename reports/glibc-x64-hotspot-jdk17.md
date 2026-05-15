---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-15 05:49:48 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 22-30 cores)</summary>

```
1778838269 24
1778838274 24
1778838279 22
1778838284 22
1778838289 22
1778838294 22
1778838299 22
1778838304 22
1778838309 26
1778838314 26
1778838319 26
1778838324 26
1778838329 30
1778838334 30
1778838339 30
1778838344 30
1778838349 30
1778838354 30
1778838359 28
1778838364 28
```
</details>

---

