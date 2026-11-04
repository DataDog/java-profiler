---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:41:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793799382 48
1793799387 48
1793799392 48
1793799397 48
1793799402 48
1793799407 48
1793799412 48
1793799417 48
1793799422 48
1793799427 48
1793799432 48
1793799437 48
1793799442 48
1793799447 48
1793799452 48
1793799457 48
1793799462 48
1793799467 48
1793799472 48
1793799477 48
```
</details>

---

