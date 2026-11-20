---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:24:39 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (4 unique values: 57-64 cores)</summary>

```
1795195220 62
1795195225 62
1795195230 62
1795195235 62
1795195240 62
1795195245 62
1795195250 62
1795195255 62
1795195260 62
1795195265 57
1795195270 57
1795195275 57
1795195280 59
1795195285 59
1795195290 59
1795195295 59
1795195300 59
1795195305 59
1795195310 59
1795195315 59
```
</details>

---

