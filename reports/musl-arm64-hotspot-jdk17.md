---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 04:47:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795426951 44
1795426956 49
1795426961 49
1795426966 49
1795426971 49
1795426976 44
1795426981 44
1795426986 44
1795426991 44
1795426996 44
1795427001 44
1795427006 44
1795427011 44
1795427016 44
1795427022 44
1795427027 44
1795427032 44
1795427037 44
1795427042 44
1795427047 49
```
</details>

---

