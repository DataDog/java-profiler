---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 08:52:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
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
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795182321 50
1795182326 50
1795182331 50
1795182336 50
1795182341 50
1795182346 50
1795182351 50
1795182356 50
1795182361 50
1795182366 50
1795182371 50
1795182376 50
1795182381 50
1795182386 50
1795182391 50
1795182396 50
1795182401 50
1795182406 50
1795182411 50
1795182416 50
```
</details>

---

