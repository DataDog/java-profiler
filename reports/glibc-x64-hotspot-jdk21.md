---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-06 04:35:13 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (5 unique values: 20-27 cores)</summary>

```
1772789338 25
1772789343 25
1772789348 25
1772789353 25
1772789358 25
1772789363 27
1772789368 27
1772789373 22
1772789378 22
1772789383 22
1772789388 22
1772789393 22
1772789398 22
1772789403 22
1772789408 22
1772789413 22
1772789418 22
1772789423 20
1772789428 20
1772789433 20
```
</details>

---

