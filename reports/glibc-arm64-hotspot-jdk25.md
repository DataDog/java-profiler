---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 05:32:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 370 |
| Sample Rate | 6.17/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (5 unique values: 37-44 cores)</summary>

```
1793615300 44
1793615305 44
1793615310 44
1793615315 39
1793615320 39
1793615325 39
1793615330 39
1793615335 37
1793615340 37
1793615345 39
1793615350 39
1793615355 39
1793615360 39
1793615365 39
1793615370 37
1793615375 37
1793615380 41
1793615385 41
1793615390 41
1793615395 41
```
</details>

---

