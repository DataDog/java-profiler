---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:56:27 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 56-67 cores)</summary>

```
1795171835 58
1795171841 58
1795171846 58
1795171851 58
1795171856 58
1795171861 58
1795171866 58
1795171871 58
1795171876 58
1795171881 58
1795171886 58
1795171891 56
1795171896 56
1795171901 56
1795171906 56
1795171911 56
1795171916 56
1795171921 65
1795171926 65
1795171931 67
```
</details>

---

