---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 08:29:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 24-62 cores)</summary>

```
1791289466 62
1791289471 62
1791289476 62
1791289481 62
1791289486 62
1791289491 62
1791289496 62
1791289501 62
1791289506 62
1791289511 24
1791289516 24
1791289521 24
1791289526 32
1791289531 32
1791289536 32
1791289541 32
1791289546 32
1791289551 32
1791289556 32
1791289561 32
```
</details>

---

