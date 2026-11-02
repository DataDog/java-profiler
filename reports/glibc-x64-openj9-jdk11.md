---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:00:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 23-56 cores)</summary>

```
1793631314 23
1793631319 23
1793631324 23
1793631329 23
1793631334 23
1793631339 23
1793631344 23
1793631349 23
1793631354 23
1793631359 23
1793631364 23
1793631369 56
1793631374 56
1793631379 56
1793631384 56
1793631389 56
1793631394 56
1793631399 56
1793631404 56
1793631409 56
```
</details>

---

