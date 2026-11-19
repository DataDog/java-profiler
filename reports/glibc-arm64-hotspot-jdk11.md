---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 11:31:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 38-50 cores)</summary>

```
1795105640 38
1795105645 38
1795105650 38
1795105655 38
1795105660 50
1795105665 50
1795105670 50
1795105675 50
1795105680 50
1795105685 50
1795105690 50
1795105695 50
1795105700 50
1795105705 50
1795105710 50
1795105715 50
1795105720 50
1795105725 50
1795105730 50
1795105735 50
```
</details>

---

