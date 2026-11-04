---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:02:40 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 61-72 cores)</summary>

```
1793829478 72
1793829483 70
1793829488 70
1793829493 70
1793829498 70
1793829503 70
1793829508 70
1793829513 70
1793829518 70
1793829523 70
1793829528 70
1793829533 70
1793829538 66
1793829543 66
1793829548 66
1793829553 66
1793829558 61
1793829563 61
1793829568 61
1793829573 61
```
</details>

---

