---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:20:02 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
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
1795015067 28
1795015072 28
1795015077 28
1795015082 33
```
</details>

---

