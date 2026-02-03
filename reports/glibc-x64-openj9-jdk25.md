---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:55:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 12 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 25-28 cores)</summary>

```
1770137438 25
1770137443 25
1770137448 25
1770137453 25
1770137458 25
1770137463 28
1770137468 28
1770137473 28
1770137478 28
1770137483 28
1770137488 28
1770137493 28
1770137498 28
1770137503 28
1770137508 28
1770137513 28
1770137518 28
1770137523 28
1770137528 28
1770137533 28
```
</details>

---

