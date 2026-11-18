---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:20:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 12 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1795014972 31
1795014977 31
1795014982 31
1795014987 31
1795014992 31
1795014997 31
1795015002 31
1795015007 31
1795015012 31
1795015017 31
1795015022 31
1795015027 31
1795015032 31
1795015037 31
1795015042 31
1795015047 31
1795015052 31
1795015057 31
1795015062 31
1795015067 31
```
</details>

---

