---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:26:18 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (2 unique values: 21-23 cores)</summary>

```
1794572468 23
1794572473 23
1794572478 23
1794572483 23
1794572488 23
1794572493 23
1794572498 23
1794572503 23
1794572508 21
1794572513 21
1794572518 21
1794572523 21
1794572528 21
1794572533 21
1794572538 21
1794572543 21
1794572548 21
1794572553 21
1794572558 21
1794572563 21
```
</details>

---

