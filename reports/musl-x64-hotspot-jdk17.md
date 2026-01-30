---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-30 06:15:42 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 9 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1769771388 29
1769771393 29
1769771398 29
1769771403 29
1769771408 29
1769771413 29
1769771418 29
1769771423 29
1769771428 29
1769771433 29
1769771438 29
1769771443 32
1769771448 32
1769771453 32
1769771458 32
1769771463 32
1769771468 32
1769771473 32
1769771478 30
1769771483 30
```
</details>

---

