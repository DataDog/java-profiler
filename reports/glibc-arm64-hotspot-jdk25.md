---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-07 14:42:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1786127877 32
1786127882 32
1786127887 32
1786127892 32
1786127897 32
1786127902 32
1786127907 32
1786127912 32
1786127917 32
1786127922 32
1786127927 32
1786127932 32
1786127937 32
1786127942 32
1786127947 32
1786127952 32
1786127957 32
1786127962 32
1786127967 32
1786127972 32
```
</details>

---

