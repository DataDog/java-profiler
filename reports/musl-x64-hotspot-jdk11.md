---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 08:29:12 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 63-96 cores)</summary>

```
1791289466 63
1791289471 63
1791289476 63
1791289481 63
1791289486 96
1791289491 96
1791289496 96
1791289501 96
1791289506 96
1791289511 96
1791289516 96
1791289521 96
1791289526 96
1791289531 96
1791289536 96
1791289541 96
1791289546 96
1791289551 96
1791289556 96
1791289561 96
```
</details>

---

