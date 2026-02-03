---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 11:55:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 10 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 86-96 cores)</summary>

```
1770137438 96
1770137443 96
1770137448 96
1770137453 96
1770137458 96
1770137463 96
1770137468 96
1770137473 96
1770137478 96
1770137483 96
1770137488 86
1770137493 86
1770137498 86
1770137503 86
1770137508 86
1770137513 86
1770137518 86
1770137523 86
1770137528 86
1770137533 86
```
</details>

---

