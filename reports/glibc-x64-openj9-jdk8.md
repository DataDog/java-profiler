---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-27 20:01:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 341 |
| Sample Rate | 5.68/sec |
| Health Score | 355% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 19-66 cores)</summary>

```
1793145466 66
1793145471 66
1793145476 66
1793145481 66
1793145486 66
1793145491 66
1793145496 66
1793145501 66
1793145506 66
1793145511 66
1793145516 66
1793145521 66
1793145526 66
1793145531 19
1793145536 19
1793145541 19
1793145546 19
1793145551 19
1793145556 19
1793145561 19
```
</details>

---

