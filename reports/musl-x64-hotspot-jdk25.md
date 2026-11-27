---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 06:24:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 14-44 cores)</summary>

```
1795778392 14
1795778397 14
1795778402 14
1795778407 14
1795778412 14
1795778417 14
1795778422 37
1795778427 37
1795778432 37
1795778437 37
1795778442 37
1795778447 37
1795778452 16
1795778457 16
1795778462 44
1795778467 44
1795778472 44
1795778477 44
1795778482 44
1795778487 44
```
</details>

---

