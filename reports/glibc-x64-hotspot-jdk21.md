---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:38:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 51-69 cores)</summary>

```
1789716454 67
1789716459 67
1789716464 69
1789716469 69
1789716474 53
1789716479 53
1789716484 55
1789716489 55
1789716494 55
1789716499 53
1789716504 53
1789716509 55
1789716514 55
1789716519 53
1789716524 53
1789716529 53
1789716534 51
1789716539 51
1789716544 51
1789716549 51
```
</details>

---

