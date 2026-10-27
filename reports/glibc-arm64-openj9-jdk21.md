---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 15:45:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 12 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1793129998 14
1793130003 14
1793130008 14
1793130013 14
1793130018 14
1793130023 14
1793130028 14
1793130033 14
1793130038 14
1793130043 14
1793130048 14
1793130053 14
1793130058 14
1793130063 14
1793130068 14
1793130073 9
1793130078 9
1793130083 9
1793130088 9
1793130093 9
```
</details>

---

