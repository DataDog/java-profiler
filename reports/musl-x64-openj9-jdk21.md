---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-29 06:49:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1017 |
| Sample Rate | 16.95/sec |
| Health Score | 1059% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 75-87 cores)</summary>

```
1777459429 75
1777459434 75
1777459439 75
1777459444 75
1777459449 75
1777459454 75
1777459459 75
1777459464 75
1777459469 75
1777459474 75
1777459479 78
1777459484 78
1777459489 78
1777459494 78
1777459499 78
1777459504 78
1777459509 78
1777459514 78
1777459519 87
1777459524 87
```
</details>

---

