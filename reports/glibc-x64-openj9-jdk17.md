---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:44:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 33-54 cores)</summary>

```
1789731599 33
1789731604 33
1789731609 33
1789731614 33
1789731619 33
1789731624 54
1789731629 54
1789731634 54
1789731639 54
1789731644 54
1789731649 54
1789731654 54
1789731659 54
1789731664 54
1789731669 54
1789731674 54
1789731679 54
1789731684 54
1789731689 54
1789731694 54
```
</details>

---

