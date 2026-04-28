---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 15:54:54 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 72-78 cores)</summary>

```
1777405592 76
1777405597 76
1777405602 74
1777405607 74
1777405612 74
1777405617 74
1777405622 74
1777405627 74
1777405632 77
1777405637 77
1777405642 77
1777405647 72
1777405652 72
1777405657 76
1777405662 76
1777405667 78
1777405672 78
1777405677 78
1777405682 78
1777405687 78
```
</details>

---

