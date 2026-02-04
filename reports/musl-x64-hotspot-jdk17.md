---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-04 10:23:40 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 12 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (7 unique values: 79-96 cores)</summary>

```
1770218286 96
1770218291 96
1770218296 96
1770218301 92
1770218306 92
1770218311 92
1770218316 92
1770218321 92
1770218326 92
1770218331 92
1770218336 86
1770218341 86
1770218346 86
1770218351 86
1770218356 86
1770218361 84
1770218366 84
1770218371 83
1770218376 83
1770218381 83
```
</details>

---

