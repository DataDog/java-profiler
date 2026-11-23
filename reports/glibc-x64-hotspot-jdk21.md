---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:59:57 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 80-85 cores)</summary>

```
1795431357 85
1795431362 83
1795431367 83
1795431372 83
1795431377 83
1795431382 83
1795431387 83
1795431392 83
1795431397 83
1795431402 83
1795431407 83
1795431412 82
1795431417 82
1795431422 82
1795431428 82
1795431433 82
1795431438 82
1795431443 82
1795431448 82
1795431453 82
```
</details>

---

