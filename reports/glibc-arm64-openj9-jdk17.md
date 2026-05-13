---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-13 09:58:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 48-59 cores)</summary>

```
1778680415 59
1778680420 59
1778680425 59
1778680430 59
1778680435 59
1778680440 59
1778680445 59
1778680451 59
1778680456 59
1778680461 59
1778680466 53
1778680471 53
1778680476 53
1778680481 53
1778680486 53
1778680491 53
1778680496 53
1778680501 53
1778680506 53
1778680511 53
```
</details>

---

