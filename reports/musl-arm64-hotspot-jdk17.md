---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 08:41:08 EST

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
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (6 unique values: 35-45 cores)</summary>

```
1793799372 35
1793799377 35
1793799383 35
1793799388 35
1793799393 35
1793799398 35
1793799403 35
1793799408 35
1793799413 37
1793799418 37
1793799423 37
1793799428 37
1793799433 37
1793799438 42
1793799443 42
1793799448 42
1793799453 42
1793799458 44
1793799463 44
1793799468 43
```
</details>

---

