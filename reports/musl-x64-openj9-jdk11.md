---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:44:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 571 |

<details>
<summary>CPU Timeline (3 unique values: 38-46 cores)</summary>

```
1789731584 40
1789731589 40
1789731594 40
1789731599 40
1789731604 40
1789731609 40
1789731614 40
1789731619 40
1789731624 40
1789731629 40
1789731634 40
1789731639 40
1789731644 40
1789731649 38
1789731654 38
1789731659 38
1789731665 46
1789731670 46
1789731675 46
1789731680 46
```
</details>

---

