---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-26 16:34:19 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1777235416 86
1777235421 86
1777235426 86
1777235431 86
1777235436 86
1777235441 86
1777235446 86
1777235451 86
1777235456 86
1777235461 88
1777235466 88
1777235471 88
1777235476 88
1777235481 88
1777235486 88
1777235491 88
1777235496 88
1777235501 88
1777235506 88
1777235511 88
```
</details>

---

