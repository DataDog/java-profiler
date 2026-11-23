---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:01:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 14 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795431322 64
1795431327 64
1795431332 64
1795431337 64
1795431342 64
1795431347 64
1795431352 64
1795431357 64
1795431362 64
1795431367 64
1795431372 64
1795431377 64
1795431382 64
1795431387 64
1795431392 64
1795431397 64
1795431402 64
1795431407 64
1795431412 64
1795431417 64
```
</details>

---

