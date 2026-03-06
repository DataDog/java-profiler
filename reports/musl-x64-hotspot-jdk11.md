---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-06 04:35:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1149 |
| Sample Rate | 19.15/sec |
| Health Score | 1197% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 59-62 cores)</summary>

```
1772789323 59
1772789328 59
1772789333 59
1772789338 59
1772789343 59
1772789348 59
1772789353 59
1772789358 59
1772789363 59
1772789368 59
1772789373 59
1772789378 62
1772789383 62
1772789388 62
1772789393 62
1772789398 62
1772789403 62
1772789408 62
1772789413 62
1772789418 62
```
</details>

---

