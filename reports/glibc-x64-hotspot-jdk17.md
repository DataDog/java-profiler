---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 08:17:25 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 17.17/sec |
| Health Score | 1073% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 21.90/sec |
| Health Score | 1369% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (7 unique values: 53-75 cores)</summary>

```
1769692302 74
1769692307 74
1769692312 74
1769692317 74
1769692322 72
1769692327 72
1769692332 70
1769692337 70
1769692342 70
1769692347 70
1769692352 70
1769692357 70
1769692362 70
1769692367 68
1769692372 68
1769692377 75
1769692382 75
1769692387 75
1769692392 75
1769692397 75
```
</details>

---

