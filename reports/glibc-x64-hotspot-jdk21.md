---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 06:29:48 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 7 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 21-23 cores)</summary>

```
1792578326 21
1792578331 21
1792578336 21
1792578341 21
1792578346 21
1792578351 21
1792578356 21
1792578361 21
1792578366 23
1792578371 23
1792578376 21
1792578381 21
1792578386 21
1792578391 21
1792578396 21
1792578401 21
1792578406 21
1792578411 21
1792578416 21
1792578421 21
```
</details>

---

