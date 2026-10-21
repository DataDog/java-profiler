---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 06:49:18 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 9 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (4 unique values: 41-58 cores)</summary>

```
1792579470 58
1792579475 48
1792579480 48
1792579485 48
1792579490 48
1792579495 48
1792579500 48
1792579505 48
1792579510 46
1792579515 46
1792579520 46
1792579525 46
1792579530 41
1792579535 41
1792579540 41
1792579545 41
1792579550 41
1792579555 41
1792579560 41
1792579565 41
```
</details>

---

