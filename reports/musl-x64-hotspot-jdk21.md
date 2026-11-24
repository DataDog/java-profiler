---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 00:03:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 67-69 cores)</summary>

```
1795496336 68
1795496341 68
1795496346 68
1795496351 68
1795496356 68
1795496361 68
1795496366 68
1795496371 68
1795496376 68
1795496381 68
1795496386 68
1795496391 67
1795496396 67
1795496401 67
1795496406 67
1795496411 67
1795496416 67
1795496421 69
1795496426 69
1795496431 69
```
</details>

---

