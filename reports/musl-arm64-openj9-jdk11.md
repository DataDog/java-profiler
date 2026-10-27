---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 15:45:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 9 |
| Allocations | 186 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (5 unique values: 27-35 cores)</summary>

```
1793129988 35
1793129993 35
1793129998 35
1793130003 35
1793130008 35
1793130013 33
1793130018 33
1793130023 33
1793130028 33
1793130033 33
1793130038 33
1793130043 33
1793130048 33
1793130053 33
1793130058 33
1793130063 28
1793130068 28
1793130073 27
1793130078 27
1793130083 28
```
</details>

---

