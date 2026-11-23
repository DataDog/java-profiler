---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:06:27 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (2 unique values: 69-71 cores)</summary>

```
1795449637 71
1795449642 71
1795449647 71
1795449652 71
1795449657 69
1795449662 69
1795449667 69
1795449672 69
1795449677 69
1795449682 69
1795449687 69
1795449692 69
1795449697 69
1795449702 69
1795449707 69
1795449712 69
1795449717 69
1795449722 69
1795449728 69
1795449733 69
```
</details>

---

