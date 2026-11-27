---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:54:55 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795798301 47
1795798306 47
1795798311 47
1795798316 47
1795798321 47
1795798326 47
1795798331 47
1795798336 47
1795798341 47
1795798346 47
1795798351 47
1795798356 47
1795798361 47
1795798366 47
1795798371 47
1795798376 47
1795798381 47
1795798386 47
1795798391 47
1795798396 47
```
</details>

---

