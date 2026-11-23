---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 20:29:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 12 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1795397171 62
1795397176 62
1795397181 62
1795397186 62
1795397191 62
1795397196 62
1795397201 62
1795397206 60
1795397211 60
1795397216 60
1795397221 60
1795397226 60
1795397231 60
1795397236 60
1795397241 60
1795397246 60
1795397251 60
1795397256 62
1795397261 62
1795397266 60
```
</details>

---

