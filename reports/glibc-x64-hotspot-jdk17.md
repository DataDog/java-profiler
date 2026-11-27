---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:30:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (4 unique values: 73-82 cores)</summary>

```
1795793119 73
1795793124 73
1795793129 73
1795793134 73
1795793139 73
1795793144 73
1795793149 73
1795793154 73
1795793159 73
1795793164 73
1795793169 73
1795793174 73
1795793179 73
1795793184 73
1795793189 73
1795793194 73
1795793199 82
1795793204 82
1795793209 82
1795793214 82
```
</details>

---

