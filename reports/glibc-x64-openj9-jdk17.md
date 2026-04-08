---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-08 12:50:58 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1775666674 89
1775666679 89
1775666684 89
1775666689 93
1775666694 93
1775666699 93
1775666704 93
1775666709 93
1775666714 91
1775666719 91
1775666724 91
1775666729 91
1775666734 96
1775666739 96
1775666744 96
1775666749 96
1775666754 96
1775666759 96
1775666764 96
1775666769 96
```
</details>

---

