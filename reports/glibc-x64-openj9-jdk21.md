---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 11:53:28 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (5 unique values: 71-76 cores)</summary>

```
1793288664 72
1793288669 72
1793288674 72
1793288679 72
1793288684 72
1793288689 72
1793288694 72
1793288699 72
1793288704 72
1793288709 72
1793288714 75
1793288719 75
1793288724 75
1793288729 73
1793288734 73
1793288739 73
1793288744 71
1793288749 71
1793288754 73
1793288759 73
```
</details>

---

