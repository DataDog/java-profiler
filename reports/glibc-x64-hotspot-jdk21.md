---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:27:59 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 60 |
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
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 60-68 cores)</summary>

```
1795627426 63
1795627431 63
1795627436 63
1795627441 63
1795627446 68
1795627451 68
1795627456 60
1795627461 60
1795627466 60
1795627471 60
1795627476 60
1795627481 60
1795627486 60
1795627491 60
1795627496 60
1795627501 60
1795627506 60
1795627511 60
1795627516 60
1795627521 60
```
</details>

---

