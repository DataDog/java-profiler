---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-06 10:08:43 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 22-30 cores)</summary>

```
1786024990 22
1786024995 22
1786025000 22
1786025005 22
1786025010 22
1786025015 22
1786025020 22
1786025025 22
1786025030 22
1786025035 22
1786025040 22
1786025045 30
1786025050 30
1786025055 28
1786025060 28
1786025065 27
1786025070 27
1786025075 27
1786025080 27
1786025085 27
```
</details>

---

