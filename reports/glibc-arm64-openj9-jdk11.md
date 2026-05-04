---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:21:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 182 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 854 |
| Sample Rate | 14.23/sec |
| Health Score | 889% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777857362 59
1777857367 59
1777857372 59
1777857377 59
1777857382 59
1777857387 59
1777857392 59
1777857397 59
1777857402 59
1777857408 59
1777857413 59
1777857418 64
1777857423 64
1777857428 64
1777857433 64
1777857438 64
1777857443 64
1777857448 64
1777857453 64
1777857458 64
```
</details>

---

