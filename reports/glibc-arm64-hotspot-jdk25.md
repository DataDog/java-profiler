---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 03:42:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 7 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (3 unique values: 33-40 cores)</summary>

```
1794559038 33
1794559043 33
1794559048 33
1794559053 40
1794559058 40
1794559063 40
1794559068 40
1794559073 35
1794559078 35
1794559083 35
1794559088 35
1794559093 35
1794559098 35
1794559103 35
1794559108 35
1794559113 35
1794559118 35
1794559123 35
1794559128 35
1794559133 35
```
</details>

---

