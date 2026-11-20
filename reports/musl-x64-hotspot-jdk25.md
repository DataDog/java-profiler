---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:14:03 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 53-76 cores)</summary>

```
1795169302 53
1795169307 53
1795169312 53
1795169317 53
1795169322 53
1795169327 53
1795169332 53
1795169337 53
1795169342 53
1795169347 53
1795169352 53
1795169357 65
1795169362 65
1795169367 65
1795169372 65
1795169377 76
1795169382 76
1795169387 56
1795169392 56
1795169397 56
```
</details>

---

