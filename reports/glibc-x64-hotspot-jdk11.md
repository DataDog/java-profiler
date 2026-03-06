---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-06 06:30:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 9 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 15-25 cores)</summary>

```
1772796353 25
1772796358 25
1772796363 25
1772796368 25
1772796373 25
1772796378 25
1772796383 25
1772796388 25
1772796393 20
1772796398 20
1772796403 20
1772796408 20
1772796413 20
1772796418 20
1772796423 20
1772796428 20
1772796433 20
1772796438 20
1772796443 15
1772796448 15
```
</details>

---

