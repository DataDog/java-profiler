---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 05:56:45 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 76-84 cores)</summary>

```
1792403468 78
1792403473 76
1792403478 76
1792403483 76
1792403488 76
1792403493 76
1792403498 76
1792403503 76
1792403508 76
1792403513 76
1792403518 76
1792403523 78
1792403528 78
1792403533 78
1792403538 78
1792403543 78
1792403548 84
1792403553 84
1792403558 84
1792403563 84
```
</details>

---

