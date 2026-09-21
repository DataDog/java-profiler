---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:26:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 9-11 cores)</summary>

```
1789982414 9
1789982419 9
1789982424 9
1789982429 9
1789982434 9
1789982439 9
1789982444 9
1789982449 9
1789982454 11
1789982459 11
1789982464 11
1789982469 11
1789982474 11
1789982479 11
1789982484 11
1789982489 11
1789982494 11
1789982499 11
1789982504 11
1789982509 11
```
</details>

---

