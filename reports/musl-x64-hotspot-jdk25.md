---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 03:00:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 21-41 cores)</summary>

```
1794988423 24
1794988428 24
1794988433 24
1794988438 24
1794988443 24
1794988448 24
1794988453 24
1794988458 24
1794988463 24
1794988468 24
1794988473 24
1794988478 21
1794988483 21
1794988488 21
1794988493 21
1794988498 41
1794988503 41
1794988508 41
1794988513 41
1794988518 41
```
</details>

---

