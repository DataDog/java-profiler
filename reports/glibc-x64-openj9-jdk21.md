---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:22:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 86-90 cores)</summary>

```
1793722669 90
1793722674 90
1793722679 90
1793722684 90
1793722689 90
1793722694 90
1793722699 90
1793722704 90
1793722709 90
1793722714 90
1793722719 90
1793722724 90
1793722729 90
1793722734 90
1793722739 90
1793722744 90
1793722749 90
1793722754 90
1793722759 88
1793722764 88
```
</details>

---

