---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 15:45:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 79-96 cores)</summary>

```
1793129940 79
1793129945 79
1793129950 79
1793129955 96
1793129960 96
1793129965 96
1793129970 96
1793129975 96
1793129980 96
1793129985 96
1793129990 96
1793129995 96
1793130000 96
1793130005 96
1793130010 96
1793130015 96
1793130020 96
1793130025 96
1793130030 96
1793130035 96
```
</details>

---

