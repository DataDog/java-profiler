---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-03 21:21:05 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857478 64
1777857483 64
1777857488 64
1777857493 64
1777857498 64
1777857503 64
1777857508 64
1777857513 64
1777857518 64
1777857523 64
1777857528 64
1777857533 64
1777857538 64
1777857543 64
1777857548 64
1777857553 64
1777857558 64
1777857563 64
1777857568 64
1777857573 64
```
</details>

---

