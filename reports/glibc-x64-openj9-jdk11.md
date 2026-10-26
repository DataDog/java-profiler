---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 11:06:14 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 75-78 cores)</summary>

```
1793026801 76
1793026806 76
1793026811 76
1793026816 76
1793026821 76
1793026826 76
1793026831 76
1793026836 76
1793026841 76
1793026846 76
1793026851 76
1793026856 76
1793026861 76
1793026866 76
1793026871 78
1793026876 78
1793026881 78
1793026886 78
1793026891 78
1793026896 78
```
</details>

---

