---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:01:40 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 62-76 cores)</summary>

```
1795431332 76
1795431337 76
1795431342 76
1795431347 70
1795431352 70
1795431357 68
1795431362 68
1795431367 68
1795431372 68
1795431377 68
1795431382 68
1795431387 66
1795431392 66
1795431397 66
1795431402 66
1795431407 66
1795431412 66
1795431417 66
1795431423 66
1795431428 68
```
</details>

---

