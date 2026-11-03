---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 12:58:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 435 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (4 unique values: 44-56 cores)</summary>

```
1793728355 44
1793728360 44
1793728365 44
1793728370 44
1793728375 44
1793728380 44
1793728385 52
1793728390 52
1793728395 54
1793728400 54
1793728405 54
1793728410 54
1793728415 54
1793728420 54
1793728425 54
1793728430 54
1793728435 54
1793728440 54
1793728445 54
1793728450 56
```
</details>

---

