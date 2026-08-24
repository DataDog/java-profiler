---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-24 15:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 45-51 cores)</summary>

```
1787600268 51
1787600273 51
1787600278 51
1787600283 51
1787600288 51
1787600293 51
1787600298 51
1787600303 51
1787600308 51
1787600313 51
1787600318 51
1787600323 51
1787600328 51
1787600333 51
1787600338 51
1787600343 51
1787600348 51
1787600353 51
1787600358 51
1787600363 45
```
</details>

---

