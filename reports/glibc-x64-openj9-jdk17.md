---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-02 05:49:12 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 850 |
| Sample Rate | 14.17/sec |
| Health Score | 886% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788342353 96
1788342358 96
1788342363 96
1788342368 96
1788342373 96
1788342378 96
1788342383 96
1788342388 94
1788342393 94
1788342398 94
1788342403 94
1788342408 94
1788342413 94
1788342418 94
1788342423 94
1788342428 92
1788342433 92
1788342438 92
1788342443 92
1788342448 92
```
</details>

---

