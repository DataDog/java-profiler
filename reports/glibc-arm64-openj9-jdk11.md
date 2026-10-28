---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:17:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 997 |
| Sample Rate | 16.62/sec |
| Health Score | 1039% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 25-38 cores)</summary>

```
1793185674 25
1793185679 25
1793185684 25
1793185689 25
1793185694 25
1793185699 25
1793185704 25
1793185709 25
1793185714 25
1793185719 25
1793185724 25
1793185729 25
1793185734 38
1793185739 38
1793185744 38
1793185749 38
1793185754 38
1793185759 38
1793185764 25
1793185769 25
```
</details>

---

