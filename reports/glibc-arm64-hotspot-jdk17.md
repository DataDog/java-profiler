---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 17:34:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 9 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 11 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778189423 64
1778189428 64
1778189433 59
1778189438 59
1778189443 59
1778189448 59
1778189453 59
1778189458 59
1778189463 59
1778189468 59
1778189473 59
1778189478 59
1778189483 59
1778189488 59
1778189493 59
1778189498 59
1778189503 59
1778189508 59
1778189513 59
1778189518 59
```
</details>

---

