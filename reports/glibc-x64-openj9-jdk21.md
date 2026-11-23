---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:47:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 39-58 cores)</summary>

```
1795426926 48
1795426931 48
1795426936 50
1795426941 50
1795426946 50
1795426951 50
1795426956 50
1795426961 50
1795426966 58
1795426971 58
1795426976 56
1795426981 56
1795426986 56
1795426991 56
1795426996 56
1795427001 56
1795427006 56
1795427011 56
1795427016 56
1795427021 56
```
</details>

---

