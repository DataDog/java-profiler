---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:47:44 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 14 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795099283 50
1795099288 50
1795099293 50
1795099298 50
1795099303 50
1795099308 50
1795099313 50
1795099318 50
1795099323 50
1795099328 50
1795099333 50
1795099338 50
1795099343 50
1795099348 50
1795099353 50
1795099358 50
1795099363 50
1795099368 50
1795099373 50
1795099378 50
```
</details>

---

