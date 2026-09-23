---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 11:34:39 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 56-72 cores)</summary>

```
1790177348 56
1790177353 56
1790177358 56
1790177363 56
1790177368 56
1790177373 56
1790177378 56
1790177383 64
1790177388 64
1790177393 64
1790177398 64
1790177403 64
1790177408 64
1790177413 64
1790177418 62
1790177423 62
1790177428 72
1790177433 72
1790177438 72
1790177443 72
```
</details>

---

