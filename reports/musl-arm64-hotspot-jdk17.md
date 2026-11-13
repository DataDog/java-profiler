---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:27:31 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794572493 48
1794572498 48
1794572503 48
1794572508 48
1794572513 48
1794572518 43
1794572523 43
1794572528 43
1794572533 43
1794572538 43
1794572543 43
1794572548 43
1794572553 43
1794572558 43
1794572563 43
1794572568 43
1794572573 43
1794572578 48
1794572583 48
1794572588 48
```
</details>

---

