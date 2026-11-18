---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:20:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795014962 85
1795014967 87
1795014972 87
1795014977 87
1795014982 87
1795014987 87
1795014992 87
1795014997 87
1795015002 87
1795015007 87
1795015012 87
1795015017 87
1795015022 87
1795015027 87
1795015032 87
1795015037 87
1795015042 87
1795015047 87
1795015052 87
1795015057 87
```
</details>

---

