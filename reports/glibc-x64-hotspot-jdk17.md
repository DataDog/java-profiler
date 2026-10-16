---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 04:44:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1792139954 30
1792139959 30
1792139964 28
1792139969 28
1792139974 28
1792139979 28
1792139984 28
1792139989 28
1792139994 28
1792139999 28
1792140004 28
1792140009 28
1792140014 28
1792140019 28
1792140024 28
1792140029 28
1792140034 28
1792140039 28
1792140044 28
1792140049 28
```
</details>

---

