---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 05:51:05 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778147260 64
1778147265 64
1778147270 64
1778147275 64
1778147280 64
1778147285 64
1778147290 64
1778147295 64
1778147300 64
1778147305 64
1778147310 64
1778147315 64
1778147320 64
1778147325 64
1778147330 64
1778147335 64
1778147340 64
1778147345 64
1778147350 64
1778147355 64
```
</details>

---

