---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:20:01 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 28-38 cores)</summary>

```
1795014967 38
1795014972 38
1795014977 28
1795014982 28
1795014987 28
1795014992 28
1795014997 28
1795015002 28
1795015007 28
1795015012 28
1795015017 28
1795015022 28
1795015027 28
1795015032 28
1795015037 28
1795015042 28
1795015047 28
1795015052 28
1795015057 28
1795015062 28
```
</details>

---

