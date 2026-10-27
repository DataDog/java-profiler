---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 15:45:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 73-93 cores)</summary>

```
1793129955 73
1793129960 73
1793129965 73
1793129970 73
1793129975 93
1793129980 93
1793129985 93
1793129990 93
1793129995 93
1793130000 93
1793130005 93
1793130010 93
1793130015 93
1793130020 93
1793130025 93
1793130030 93
1793130035 93
1793130040 93
1793130045 93
1793130050 93
```
</details>

---

