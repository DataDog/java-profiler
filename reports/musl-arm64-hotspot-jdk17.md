---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:00:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793098438 48
1793098443 48
1793098448 48
1793098453 48
1793098458 48
1793098463 48
1793098468 48
1793098473 48
1793098478 48
1793098483 48
1793098488 48
1793098493 48
1793098498 48
1793098503 48
1793098508 48
1793098513 48
1793098518 48
1793098523 36
1793098528 36
1793098533 36
```
</details>

---

