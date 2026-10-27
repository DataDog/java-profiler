---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 15:45:04 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 55-88 cores)</summary>

```
1793129961 60
1793129966 60
1793129971 60
1793129976 60
1793129981 60
1793129986 60
1793129991 60
1793129996 60
1793130001 55
1793130006 55
1793130011 55
1793130016 88
1793130021 88
1793130026 88
1793130031 88
1793130036 88
1793130041 88
1793130046 88
1793130051 88
1793130056 88
```
</details>

---

