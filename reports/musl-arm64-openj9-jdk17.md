---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-26 11:06:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 11 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793026816 48
1793026821 48
1793026826 48
1793026831 48
1793026836 48
1793026841 48
1793026846 48
1793026851 48
1793026856 48
1793026861 48
1793026866 48
1793026871 48
1793026876 46
1793026881 46
1793026886 46
1793026891 46
1793026896 46
1793026901 46
1793026906 46
1793026911 46
```
</details>

---

