---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 09:24:14 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 49-75 cores)</summary>

```
1795184335 49
1795184340 49
1795184345 49
1795184350 49
1795184355 49
1795184360 49
1795184365 49
1795184370 49
1795184375 49
1795184380 49
1795184385 49
1795184390 58
1795184395 58
1795184400 58
1795184405 58
1795184410 58
1795184415 58
1795184420 55
1795184425 55
1795184430 55
```
</details>

---

