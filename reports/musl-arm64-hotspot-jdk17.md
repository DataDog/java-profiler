---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-25 05:16:42 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1790327437 50
1790327442 50
1790327447 50
1790327452 50
1790327457 50
1790327463 50
1790327468 50
1790327473 50
1790327478 50
1790327483 50
1790327488 50
1790327493 50
1790327498 50
1790327503 50
1790327508 50
1790327513 50
1790327518 50
1790327523 50
1790327528 50
1790327533 64
```
</details>

---

