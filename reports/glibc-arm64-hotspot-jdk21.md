---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:32:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 8 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (5 unique values: 37-44 cores)</summary>

```
1793615298 44
1793615303 44
1793615308 44
1793615313 39
1793615318 39
1793615323 39
1793615328 39
1793615333 37
1793615338 37
1793615343 37
1793615348 39
1793615353 39
1793615358 39
1793615363 39
1793615368 37
1793615373 37
1793615378 41
1793615383 41
1793615388 41
1793615393 41
```
</details>

---

