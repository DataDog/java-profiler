---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 08:25:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 14 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 38-45 cores)</summary>

```
1795094478 45
1795094483 45
1795094488 45
1795094493 45
1795094498 45
1795094503 38
1795094508 38
1795094513 38
1795094518 38
1795094523 38
1795094528 38
1795094533 38
1795094538 38
1795094543 38
1795094548 38
1795094553 38
1795094558 38
1795094563 38
1795094568 38
1795094573 38
```
</details>

---

