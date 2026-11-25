---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:29:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (4 unique values: 41-59 cores)</summary>

```
1795620225 41
1795620230 41
1795620235 41
1795620240 41
1795620245 41
1795620250 41
1795620255 41
1795620260 41
1795620265 44
1795620270 44
1795620275 44
1795620280 44
1795620285 44
1795620290 44
1795620295 42
1795620300 42
1795620305 42
1795620310 42
1795620315 59
1795620320 59
```
</details>

---

