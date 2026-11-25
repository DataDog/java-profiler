---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:29:22 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (5 unique values: 62-69 cores)</summary>

```
1795620209 69
1795620214 69
1795620219 69
1795620224 69
1795620229 69
1795620234 69
1795620239 69
1795620244 69
1795620249 69
1795620254 66
1795620259 66
1795620264 68
1795620269 68
1795620274 68
1795620279 64
1795620284 64
1795620289 62
1795620294 62
1795620299 62
1795620304 62
```
</details>

---

