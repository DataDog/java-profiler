---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:47:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 13-49 cores)</summary>

```
1795426949 49
1795426954 49
1795426959 49
1795426964 49
1795426969 49
1795426974 33
1795426979 33
1795426984 33
1795426989 33
1795426994 33
1795426999 33
1795427004 33
1795427009 33
1795427014 33
1795427019 33
1795427024 33
1795427029 33
1795427034 33
1795427039 33
1795427044 33
```
</details>

---

