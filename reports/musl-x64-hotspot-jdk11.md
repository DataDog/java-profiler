---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:28:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 8 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794572478 32
1794572483 32
1794572488 32
1794572493 32
1794572498 32
1794572503 32
1794572508 32
1794572513 32
1794572518 32
1794572523 32
1794572528 32
1794572533 32
1794572538 32
1794572543 32
1794572548 32
1794572553 32
1794572558 32
1794572563 32
1794572568 32
1794572573 32
```
</details>

---

