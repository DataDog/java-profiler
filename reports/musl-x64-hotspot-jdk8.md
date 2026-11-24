---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-24 09:14:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-44 cores)</summary>

```
1795529310 40
1795529315 40
1795529320 40
1795529325 40
1795529330 40
1795529335 40
1795529340 40
1795529345 40
1795529350 40
1795529355 40
1795529360 44
1795529365 44
1795529370 44
1795529375 44
1795529380 44
1795529385 44
1795529390 42
1795529395 42
1795529400 42
1795529405 42
```
</details>

---

