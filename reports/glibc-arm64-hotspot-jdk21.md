---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:29:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 11 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795620270 33
1795620275 33
1795620280 33
1795620285 33
1795620290 33
1795620295 33
1795620300 33
1795620305 33
1795620310 33
1795620316 33
1795620321 33
1795620326 33
1795620331 33
1795620336 33
1795620341 33
1795620346 64
1795620351 64
1795620356 64
1795620361 64
1795620366 64
```
</details>

---

