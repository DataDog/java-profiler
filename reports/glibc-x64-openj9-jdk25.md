---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 05:44:24 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (5 unique values: 67-78 cores)</summary>

```
1777455338 67
1777455343 72
1777455348 72
1777455353 74
1777455358 74
1777455363 74
1777455368 74
1777455373 74
1777455378 74
1777455383 74
1777455388 74
1777455393 74
1777455398 78
1777455403 78
1777455408 78
1777455413 78
1777455418 78
1777455423 74
1777455428 74
1777455433 74
```
</details>

---

