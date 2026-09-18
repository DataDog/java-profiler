---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:31:08 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 36-42 cores)</summary>

```
1789716333 40
1789716338 36
1789716343 36
1789716348 38
1789716353 38
1789716358 38
1789716363 38
1789716368 40
1789716373 40
1789716378 40
1789716383 40
1789716388 40
1789716393 40
1789716398 40
1789716403 42
1789716408 42
1789716413 40
1789716418 40
1789716423 40
1789716428 42
```
</details>

---

