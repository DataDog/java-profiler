---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:23:14 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1125 |
| Sample Rate | 18.75/sec |
| Health Score | 1172% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 25-52 cores)</summary>

```
1789737476 25
1789737481 25
1789737486 25
1789737491 25
1789737496 45
1789737501 45
1789737506 45
1789737511 45
1789737516 45
1789737521 45
1789737526 45
1789737531 45
1789737536 45
1789737541 45
1789737546 45
1789737551 45
1789737556 45
1789737561 45
1789737566 45
1789737571 45
```
</details>

---

