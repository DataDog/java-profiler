---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-26 16:34:19 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1777235406 32
1777235411 32
1777235416 32
1777235421 32
1777235426 32
1777235431 32
1777235436 30
1777235441 30
1777235446 30
1777235451 30
1777235456 30
1777235461 30
1777235466 32
1777235471 32
1777235476 30
1777235481 30
1777235486 32
1777235491 32
1777235496 32
1777235501 32
```
</details>

---

