---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 05:55:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 933 |
| Sample Rate | 15.55/sec |
| Health Score | 972% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1791539392 40
1791539397 40
1791539402 40
1791539407 40
1791539412 40
1791539418 40
1791539423 40
1791539428 40
1791539433 40
1791539438 40
1791539443 40
1791539448 40
1791539453 40
1791539458 40
1791539463 40
1791539468 40
1791539473 40
1791539478 40
1791539483 48
1791539488 48
```
</details>

---

