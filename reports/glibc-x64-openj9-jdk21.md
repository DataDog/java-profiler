---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 10:46:04 EDT

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
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 312 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 11 |
| Allocations | 419 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1790087899 72
1790087904 72
1790087909 72
1790087914 72
1790087919 72
1790087924 72
1790087929 72
1790087934 72
1790087939 72
1790087944 72
1790087949 72
1790087954 72
1790087959 72
1790087964 72
1790087969 72
1790087974 72
1790087979 70
1790087984 70
1790087989 70
1790087994 70
```
</details>

---

