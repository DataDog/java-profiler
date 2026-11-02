---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 13:05:34 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 49-61 cores)</summary>

```
1793642488 51
1793642493 51
1793642498 49
1793642503 49
1793642508 49
1793642513 49
1793642518 49
1793642523 49
1793642528 49
1793642533 49
1793642538 49
1793642543 49
1793642548 49
1793642553 49
1793642558 49
1793642563 49
1793642568 49
1793642573 49
1793642578 59
1793642583 59
```
</details>

---

