---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 13:25:44 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787246461 96
1787246466 96
1787246471 96
1787246476 96
1787246481 96
1787246486 96
1787246491 96
1787246496 96
1787246501 96
1787246506 96
1787246511 96
1787246516 96
1787246521 96
1787246526 96
1787246531 88
1787246536 88
1787246541 88
1787246546 88
1787246551 88
1787246556 88
```
</details>

---

