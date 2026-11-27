---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:30:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 57-68 cores)</summary>

```
1795793082 57
1795793087 57
1795793092 57
1795793097 57
1795793102 57
1795793107 57
1795793112 57
1795793117 57
1795793122 57
1795793127 59
1795793132 59
1795793137 59
1795793142 59
1795793147 59
1795793152 59
1795793157 68
1795793162 68
1795793167 68
1795793172 66
1795793177 66
```
</details>

---

