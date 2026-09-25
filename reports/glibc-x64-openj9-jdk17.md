---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 10:31:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 70-81 cores)</summary>

```
1790346380 70
1790346385 70
1790346390 70
1790346395 70
1790346400 70
1790346405 70
1790346410 72
1790346415 72
1790346420 72
1790346425 72
1790346430 72
1790346435 72
1790346440 72
1790346445 72
1790346450 72
1790346455 72
1790346460 72
1790346465 72
1790346470 72
1790346475 72
```
</details>

---

