---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 18:32:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1778538433 53
1778538438 53
1778538443 53
1778538448 53
1778538453 53
1778538458 53
1778538463 53
1778538468 53
1778538473 53
1778538478 53
1778538483 53
1778538488 53
1778538493 53
1778538498 53
1778538503 53
1778538508 53
1778538513 53
1778538518 53
1778538523 53
1778538528 48
```
</details>

---

