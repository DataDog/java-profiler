---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 12:30:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 293 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 967 |
| Sample Rate | 16.12/sec |
| Health Score | 1007% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 86-92 cores)</summary>

```
1794245027 86
1794245032 86
1794245037 92
1794245042 92
1794245047 92
1794245052 92
1794245057 92
1794245062 92
1794245067 92
1794245072 92
1794245077 92
1794245082 92
1794245087 92
1794245092 92
1794245097 92
1794245102 92
1794245107 92
1794245112 92
1794245117 92
1794245122 90
```
</details>

---

