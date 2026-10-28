---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:01:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 67-78 cores)</summary>

```
1793184680 67
1793184685 67
1793184690 69
1793184695 69
1793184700 69
1793184705 69
1793184710 69
1793184715 69
1793184720 69
1793184725 69
1793184730 78
1793184735 78
1793184740 78
1793184745 78
1793184750 78
1793184755 78
1793184760 78
1793184765 78
1793184770 78
1793184775 78
```
</details>

---

