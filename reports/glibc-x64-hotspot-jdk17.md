---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 05:16:45 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1770113278 32
1770113283 32
1770113288 32
1770113293 32
1770113298 32
1770113303 28
1770113308 28
1770113313 28
1770113318 28
1770113323 28
1770113328 28
1770113333 28
1770113338 28
1770113343 28
1770113348 28
1770113353 28
1770113358 28
1770113363 28
1770113368 28
1770113373 28
```
</details>

---

