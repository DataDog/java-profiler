---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 16:34:35 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1778185679 30
1778185684 30
1778185689 27
1778185694 27
1778185699 27
1778185704 27
1778185709 27
1778185714 27
1778185719 27
1778185724 27
1778185729 27
1778185734 27
1778185739 27
1778185744 27
1778185749 27
1778185754 27
1778185759 27
1778185764 27
1778185769 27
1778185774 27
```
</details>

---

