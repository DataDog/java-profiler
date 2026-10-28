---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:01:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793184710 43
1793184715 43
1793184720 43
1793184725 43
1793184730 43
1793184735 43
1793184740 43
1793184745 43
1793184750 43
1793184755 43
1793184760 43
1793184765 43
1793184770 43
1793184775 43
1793184780 43
1793184785 43
1793184790 48
1793184795 48
1793184800 48
1793184805 48
```
</details>

---

