---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-25 10:31:17 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 20-30 cores)</summary>

```
1790346383 20
1790346388 20
1790346393 20
1790346398 20
1790346403 30
1790346408 30
1790346413 30
1790346418 30
1790346423 30
1790346428 30
1790346433 30
1790346438 30
1790346443 30
1790346448 30
1790346453 30
1790346458 30
1790346463 30
1790346468 30
1790346473 30
1790346478 30
```
</details>

---

