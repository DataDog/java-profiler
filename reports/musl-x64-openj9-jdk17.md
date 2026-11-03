---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 07:41:16 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 41-59 cores)</summary>

```
1793709416 59
1793709421 59
1793709426 58
1793709431 58
1793709436 58
1793709441 58
1793709446 58
1793709451 58
1793709456 58
1793709461 58
1793709466 58
1793709471 58
1793709476 41
1793709481 41
1793709486 43
1793709491 43
1793709496 43
1793709501 43
1793709506 43
1793709511 43
```
</details>

---

