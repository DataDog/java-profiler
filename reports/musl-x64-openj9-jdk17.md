---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:01:16 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 10 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (3 unique values: 73-77 cores)</summary>

```
1793184705 77
1793184710 77
1793184715 77
1793184720 77
1793184725 75
1793184730 75
1793184735 75
1793184740 75
1793184745 73
1793184750 73
1793184755 73
1793184760 73
1793184765 73
1793184770 73
1793184775 73
1793184780 73
1793184785 73
1793184790 73
1793184795 73
1793184800 73
```
</details>

---

