---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:07:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 14 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795619020 44
1795619025 44
1795619030 44
1795619035 44
1795619040 44
1795619045 44
1795619050 44
1795619055 44
1795619060 44
1795619065 44
1795619070 44
1795619075 44
1795619080 44
1795619085 44
1795619090 49
1795619095 49
1795619100 49
1795619105 49
1795619110 49
1795619115 49
```
</details>

---

