---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 13:16:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 9-25 cores)</summary>

```
1791220391 23
1791220396 23
1791220401 23
1791220406 23
1791220411 25
1791220416 25
1791220421 25
1791220426 25
1791220431 25
1791220436 25
1791220441 25
1791220446 25
1791220451 25
1791220456 25
1791220461 25
1791220466 25
1791220471 18
1791220476 18
1791220481 9
1791220486 9
```
</details>

---

