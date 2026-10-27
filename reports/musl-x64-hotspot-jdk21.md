---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:00:19 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1793098428 51
1793098433 56
1793098438 56
1793098443 56
1793098448 56
1793098453 56
1793098458 56
1793098463 56
1793098468 56
1793098473 56
1793098478 56
1793098483 56
1793098488 56
1793098493 56
1793098498 56
1793098503 56
1793098508 56
1793098513 56
1793098518 56
1793098523 56
```
</details>

---

