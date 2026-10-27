---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 15:45:03 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 923 |
| Sample Rate | 15.38/sec |
| Health Score | 961% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 31-48 cores)</summary>

```
1793130003 48
1793130008 48
1793130013 48
1793130018 48
1793130023 48
1793130028 48
1793130033 48
1793130038 48
1793130043 48
1793130048 48
1793130053 48
1793130058 31
1793130063 31
1793130068 31
1793130073 31
1793130078 31
1793130083 31
1793130088 48
1793130093 48
1793130098 48
```
</details>

---

