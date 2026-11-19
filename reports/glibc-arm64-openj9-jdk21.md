---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 08:25:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (4 unique values: 15-34 cores)</summary>

```
1795094443 20
1795094448 20
1795094453 20
1795094458 20
1795094463 15
1795094468 15
1795094473 15
1795094478 15
1795094483 29
1795094488 29
1795094493 29
1795094498 29
1795094503 29
1795094508 29
1795094513 29
1795094518 29
1795094523 34
1795094528 34
1795094533 34
1795094538 34
```
</details>

---

