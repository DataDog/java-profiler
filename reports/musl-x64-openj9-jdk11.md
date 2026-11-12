---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 18:03:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 989 |
| Sample Rate | 16.48/sec |
| Health Score | 1030% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 66-69 cores)</summary>

```
1794524330 68
1794524335 68
1794524340 68
1794524345 68
1794524350 68
1794524355 66
1794524360 66
1794524365 66
1794524370 66
1794524375 66
1794524380 66
1794524385 66
1794524390 66
1794524395 66
1794524400 66
1794524405 68
1794524410 68
1794524415 68
1794524420 68
1794524425 68
```
</details>

---

