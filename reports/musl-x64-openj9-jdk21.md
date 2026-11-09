---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 12:30:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 940 |
| Sample Rate | 15.67/sec |
| Health Score | 979% |
| Threads | 13 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 58-64 cores)</summary>

```
1794245047 62
1794245052 62
1794245057 64
1794245062 64
1794245067 64
1794245072 64
1794245077 64
1794245082 64
1794245087 64
1794245092 64
1794245097 64
1794245102 64
1794245107 64
1794245112 64
1794245117 64
1794245122 60
1794245127 60
1794245132 58
1794245137 58
1794245142 58
```
</details>

---

