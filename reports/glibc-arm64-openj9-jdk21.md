---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-07 14:42:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 11 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786127897 43
1786127902 43
1786127907 43
1786127912 48
1786127917 48
1786127922 48
1786127927 48
1786127932 48
1786127937 48
1786127942 48
1786127947 48
1786127952 48
1786127957 48
1786127962 48
1786127967 48
1786127972 48
1786127977 48
1786127982 48
1786127987 48
1786127992 48
```
</details>

---

