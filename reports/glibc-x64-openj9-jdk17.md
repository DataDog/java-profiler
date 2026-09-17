---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 19:10:08 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 84-90 cores)</summary>

```
1789686339 86
1789686344 86
1789686349 84
1789686354 84
1789686359 86
1789686364 86
1789686369 86
1789686374 86
1789686379 86
1789686384 86
1789686389 86
1789686394 86
1789686399 86
1789686404 88
1789686409 88
1789686414 90
1789686419 90
1789686424 90
1789686429 90
1789686434 90
```
</details>

---

