---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:27:22 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1790173276 50
1790173281 50
1790173286 50
1790173291 50
1790173296 50
1790173301 50
1790173306 50
1790173311 50
1790173316 50
1790173321 50
1790173326 50
1790173331 50
1790173336 64
1790173341 64
1790173346 50
1790173351 50
1790173356 50
1790173361 50
1790173366 50
1790173371 50
```
</details>

---

