---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 14:04:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (6 unique values: 52-76 cores)</summary>

```
1786557612 76
1786557617 76
1786557622 76
1786557627 76
1786557632 56
1786557637 56
1786557642 54
1786557647 54
1786557652 52
1786557657 52
1786557662 52
1786557667 52
1786557672 52
1786557677 52
1786557682 54
1786557687 54
1786557692 54
1786557697 54
1786557702 54
1786557707 54
```
</details>

---

