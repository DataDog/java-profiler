---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-27 11:54:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1795798275 57
1795798280 57
1795798285 57
1795798290 57
1795798296 57
1795798301 57
1795798306 57
1795798311 57
1795798316 57
1795798321 57
1795798326 57
1795798331 57
1795798336 57
1795798341 59
1795798346 59
1795798351 59
1795798356 57
1795798361 57
1795798366 57
1795798371 57
```
</details>

---

