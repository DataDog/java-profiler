---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:39:51 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 72-79 cores)</summary>

```
1795451632 72
1795451637 72
1795451642 72
1795451647 72
1795451652 72
1795451657 74
1795451662 74
1795451667 74
1795451672 74
1795451677 74
1795451682 74
1795451687 74
1795451692 79
1795451697 79
1795451702 79
1795451707 77
1795451712 77
1795451717 75
1795451722 75
1795451727 75
```
</details>

---

