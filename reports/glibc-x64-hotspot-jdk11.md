---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 07:42:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1793882291 28
1793882296 28
1793882301 28
1793882306 30
1793882311 30
1793882316 30
1793882321 30
1793882326 32
1793882331 32
1793882336 27
1793882341 27
1793882346 27
1793882351 27
1793882356 27
1793882361 27
1793882366 27
1793882371 27
1793882376 27
1793882381 27
1793882386 27
```
</details>

---

