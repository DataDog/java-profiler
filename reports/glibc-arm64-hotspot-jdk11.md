---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:45:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 12 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794497493 36
1794497498 36
1794497503 36
1794497508 36
1794497513 36
1794497518 36
1794497523 36
1794497528 36
1794497533 36
1794497538 36
1794497543 36
1794497548 36
1794497553 36
1794497558 36
1794497563 48
1794497568 48
1794497573 48
1794497578 48
1794497583 48
1794497588 48
```
</details>

---

