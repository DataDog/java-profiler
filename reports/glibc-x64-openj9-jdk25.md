---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 10 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793995760 62
1793995765 62
1793995770 62
1793995775 62
1793995780 62
1793995785 62
1793995790 62
1793995795 62
1793995800 62
1793995805 62
1793995810 62
1793995815 62
1793995820 62
1793995825 64
1793995830 64
1793995835 64
1793995840 64
1793995845 64
1793995850 64
1793995855 64
```
</details>

---

