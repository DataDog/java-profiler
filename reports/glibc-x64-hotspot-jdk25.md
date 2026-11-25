---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:00:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (5 unique values: 75-85 cores)</summary>

```
1795618464 75
1795618469 75
1795618474 75
1795618479 75
1795618484 78
1795618489 78
1795618494 78
1795618499 78
1795618504 78
1795618509 78
1795618514 78
1795618519 78
1795618524 78
1795618529 78
1795618534 80
1795618539 80
1795618544 78
1795618549 78
1795618554 80
1795618559 80
```
</details>

---

