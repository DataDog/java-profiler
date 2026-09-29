---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-29 02:36:41 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1790663429 35
1790663434 35
1790663439 35
1790663444 40
1790663449 40
1790663454 40
1790663459 40
1790663464 40
1790663469 40
1790663474 40
1790663479 40
1790663484 40
1790663490 40
1790663495 40
1790663500 40
1790663505 40
1790663510 40
1790663515 40
1790663520 40
1790663525 40
```
</details>

---

