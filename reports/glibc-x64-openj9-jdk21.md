---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 17:34:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 12 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 82-92 cores)</summary>

```
1778189403 82
1778189408 84
1778189413 84
1778189418 84
1778189423 84
1778189428 84
1778189433 89
1778189438 89
1778189443 89
1778189448 89
1778189453 89
1778189458 89
1778189463 89
1778189468 89
1778189473 92
1778189478 92
1778189483 92
1778189488 92
1778189493 92
1778189498 92
```
</details>

---

