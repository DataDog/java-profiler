---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 10:44:18 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 10 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 940 |
| Sample Rate | 15.67/sec |
| Health Score | 979% |
| Threads | 13 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1770132780 94
1770132785 94
1770132790 94
1770132795 94
1770132800 94
1770132805 94
1770132810 94
1770132815 94
1770132820 94
1770132825 94
1770132830 94
1770132835 94
1770132840 94
1770132845 94
1770132850 94
1770132855 94
1770132860 96
1770132865 96
1770132870 96
1770132875 96
```
</details>

---

