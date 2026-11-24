---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 12:21:55 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (4 unique values: 76-80 cores)</summary>

```
1795540624 78
1795540629 78
1795540634 80
1795540639 80
1795540644 80
1795540649 80
1795540654 80
1795540659 78
1795540664 78
1795540669 78
1795540674 78
1795540679 78
1795540684 78
1795540689 80
1795540694 80
1795540699 80
1795540704 76
1795540709 76
1795540714 76
1795540719 76
```
</details>

---

