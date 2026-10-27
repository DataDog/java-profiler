---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 15:45:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 11-31 cores)</summary>

```
1793130002 31
1793130007 31
1793130013 11
1793130018 11
1793130023 11
1793130028 11
1793130033 28
1793130038 28
1793130043 11
1793130048 11
1793130053 11
1793130058 11
1793130063 11
1793130068 11
1793130073 11
1793130078 11
1793130083 11
1793130088 11
1793130093 11
1793130098 11
```
</details>

---

