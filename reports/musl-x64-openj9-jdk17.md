---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 06:43:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1778582320 64
1778582325 64
1778582331 64
1778582336 64
1778582341 64
1778582346 64
1778582351 64
1778582356 64
1778582361 64
1778582366 64
1778582371 64
1778582376 64
1778582381 64
1778582386 64
1778582391 64
1778582396 64
1778582401 64
1778582406 64
1778582411 62
1778582416 62
```
</details>

---

