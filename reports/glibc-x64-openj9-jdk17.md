---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 12:28:39 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 81 |
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
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 78-86 cores)</summary>

```
1792772663 86
1792772668 86
1792772673 86
1792772678 86
1792772683 78
1792772688 78
1792772693 78
1792772699 78
1792772704 78
1792772709 78
1792772714 78
1792772719 78
1792772724 78
1792772729 78
1792772734 78
1792772739 78
1792772744 78
1792772749 78
1792772754 78
1792772759 78
```
</details>

---

