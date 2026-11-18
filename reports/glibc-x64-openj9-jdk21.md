---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 03:00:21 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 24-46 cores)</summary>

```
1794988427 46
1794988432 46
1794988437 46
1794988442 44
1794988447 44
1794988452 44
1794988457 44
1794988462 44
1794988467 44
1794988472 44
1794988477 44
1794988482 46
1794988487 46
1794988492 46
1794988497 46
1794988502 46
1794988507 46
1794988512 46
1794988517 24
1794988522 24
```
</details>

---

