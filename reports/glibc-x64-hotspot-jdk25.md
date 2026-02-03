---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 05:16:45 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 12 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1770113272 23
1770113277 23
1770113282 23
1770113287 23
1770113292 23
1770113297 23
1770113302 32
1770113307 32
1770113312 32
1770113317 32
1770113322 32
1770113327 32
1770113332 32
1770113337 32
1770113342 32
1770113347 32
1770113352 32
1770113357 32
1770113362 32
1770113367 32
```
</details>

---

