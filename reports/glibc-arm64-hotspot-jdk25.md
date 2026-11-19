---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 09:47:44 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 11 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 45-64 cores)</summary>

```
1795099293 59
1795099298 59
1795099303 59
1795099308 59
1795099313 59
1795099318 59
1795099323 59
1795099328 64
1795099333 64
1795099338 64
1795099343 64
1795099348 64
1795099353 64
1795099358 64
1795099363 64
1795099368 64
1795099373 64
1795099378 64
1795099383 64
1795099388 59
```
</details>

---

