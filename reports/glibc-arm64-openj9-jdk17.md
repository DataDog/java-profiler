---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-06 15:13:42 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793995750 48
1793995755 48
1793995760 48
1793995765 48
1793995770 48
1793995775 48
1793995780 48
1793995785 43
1793995790 43
1793995795 43
1793995800 43
1793995805 43
1793995810 43
1793995815 43
1793995820 43
1793995825 43
1793995830 43
1793995835 43
1793995840 43
1793995845 43
```
</details>

---

