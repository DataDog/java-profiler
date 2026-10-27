---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 15:45:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 8 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793129935 32
1793129940 32
1793129945 32
1793129950 32
1793129955 32
1793129960 32
1793129965 32
1793129970 32
1793129975 32
1793129980 32
1793129985 32
1793129990 32
1793129995 32
1793130000 32
1793130005 32
1793130010 32
1793130015 32
1793130020 32
1793130025 32
1793130030 32
```
</details>

---

