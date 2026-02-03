---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 05:16:48 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 14-32 cores)</summary>

```
1770113273 14
1770113278 14
1770113283 14
1770113288 14
1770113293 14
1770113298 14
1770113303 14
1770113308 14
1770113313 14
1770113318 14
1770113323 14
1770113328 14
1770113333 14
1770113338 32
1770113343 32
1770113348 32
1770113353 32
1770113358 32
1770113363 32
1770113368 32
```
</details>

---

