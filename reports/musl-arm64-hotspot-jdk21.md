---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 08:25:42 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 15 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 36-50 cores)</summary>

```
1795094438 50
1795094443 50
1795094448 50
1795094453 50
1795094458 50
1795094463 50
1795094468 50
1795094473 50
1795094478 50
1795094483 50
1795094488 50
1795094493 50
1795094498 50
1795094503 50
1795094508 50
1795094513 50
1795094518 50
1795094523 50
1795094528 50
1795094533 50
```
</details>

---

