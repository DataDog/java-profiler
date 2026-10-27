---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-27 15:45:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1793129940 30
1793129945 30
1793129950 30
1793129955 30
1793129960 30
1793129965 30
1793129970 30
1793129975 30
1793129980 30
1793129985 30
1793129990 30
1793129995 30
1793130000 30
1793130005 30
1793130010 30
1793130015 30
1793130020 30
1793130025 28
1793130030 28
1793130035 28
```
</details>

---

