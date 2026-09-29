---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 06:43:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 80-84 cores)</summary>

```
1790678279 84
1790678284 84
1790678289 84
1790678294 84
1790678299 84
1790678304 84
1790678309 84
1790678314 84
1790678319 84
1790678324 84
1790678329 80
1790678334 80
1790678339 80
1790678344 80
1790678349 80
1790678354 80
1790678359 80
1790678364 80
1790678369 80
1790678374 80
```
</details>

---

