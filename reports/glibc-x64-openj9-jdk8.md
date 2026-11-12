---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-12 07:47:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 61-72 cores)</summary>

```
1794487336 72
1794487341 72
1794487346 72
1794487351 72
1794487356 72
1794487361 72
1794487366 72
1794487371 70
1794487376 70
1794487381 70
1794487386 70
1794487391 61
1794487396 61
1794487401 61
1794487406 61
1794487411 61
1794487416 61
1794487421 61
1794487426 61
1794487431 61
```
</details>

---

