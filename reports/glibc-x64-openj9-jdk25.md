---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:06:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 10 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 71-79 cores)</summary>

```
1795449637 73
1795449642 73
1795449647 73
1795449652 71
1795449657 71
1795449662 71
1795449667 71
1795449672 71
1795449677 71
1795449682 71
1795449687 79
1795449692 79
1795449697 79
1795449702 79
1795449707 79
1795449712 79
1795449717 79
1795449722 79
1795449727 79
1795449732 79
```
</details>

---

