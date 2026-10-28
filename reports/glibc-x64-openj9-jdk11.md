---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 20:01:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1793145471 30
1793145476 30
1793145481 30
1793145486 30
1793145491 30
1793145496 30
1793145501 30
1793145506 30
1793145511 30
1793145516 30
1793145521 30
1793145526 30
1793145531 30
1793145536 30
1793145541 32
1793145546 32
1793145551 32
1793145556 32
1793145561 32
1793145566 32
```
</details>

---

