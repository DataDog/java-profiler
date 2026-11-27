---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 06:24:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 7 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1795778393 75
1795778398 75
1795778403 75
1795778408 75
1795778413 75
1795778418 75
1795778423 75
1795778428 75
1795778433 77
1795778438 77
1795778443 77
1795778448 77
1795778453 77
1795778458 77
1795778463 77
1795778468 77
1795778473 77
1795778478 77
1795778483 77
1795778488 77
```
</details>

---

