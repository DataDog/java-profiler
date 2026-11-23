---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:59:59 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 74-82 cores)</summary>

```
1795431347 82
1795431352 82
1795431357 82
1795431362 82
1795431367 82
1795431372 82
1795431377 82
1795431382 82
1795431387 82
1795431392 82
1795431397 82
1795431402 82
1795431407 82
1795431412 74
1795431417 74
1795431422 74
1795431427 74
1795431432 74
1795431437 74
1795431442 74
```
</details>

---

