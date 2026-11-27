---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 10:30:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 10 |
| Allocations | 30 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (4 unique values: 52-57 cores)</summary>

```
1795793082 55
1795793087 55
1795793092 53
1795793097 53
1795793102 53
1795793107 53
1795793112 53
1795793117 53
1795793122 53
1795793127 53
1795793132 57
1795793137 57
1795793142 57
1795793147 57
1795793152 52
1795793157 52
1795793162 52
1795793167 52
1795793172 52
1795793177 52
```
</details>

---

