---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 00:03:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (6 unique values: 28-68 cores)</summary>

```
1795496336 40
1795496341 40
1795496346 40
1795496351 68
1795496356 68
1795496361 68
1795496366 68
1795496371 68
1795496376 68
1795496381 47
1795496386 47
1795496391 30
1795496396 30
1795496401 30
1795496406 30
1795496411 30
1795496416 30
1795496421 28
1795496426 28
1795496431 28
```
</details>

---

