---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 07:16:42 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1786446599 43
1786446604 43
1786446609 43
1786446614 43
1786446619 43
1786446624 43
1786446629 43
1786446634 43
1786446639 43
1786446644 43
1786446649 43
1786446654 43
1786446659 41
1786446664 41
1786446669 41
1786446674 41
1786446679 41
1786446684 41
1786446689 43
1786446694 43
```
</details>

---

