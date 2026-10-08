---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 05:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1791450250 32
1791450255 32
1791450260 27
1791450265 27
1791450270 27
1791450275 27
1791450280 27
1791450286 27
1791450291 27
1791450296 27
1791450301 27
1791450306 27
1791450311 32
1791450316 32
1791450321 32
1791450326 32
1791450331 32
1791450336 32
1791450341 32
1791450346 32
```
</details>

---

