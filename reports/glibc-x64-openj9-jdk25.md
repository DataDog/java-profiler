---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:35:45 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 40-51 cores)</summary>

```
1795112824 51
1795112829 51
1795112834 51
1795112839 51
1795112844 51
1795112849 51
1795112854 51
1795112859 51
1795112864 49
1795112869 49
1795112874 49
1795112879 49
1795112884 49
1795112889 49
1795112894 49
1795112899 49
1795112904 40
1795112909 40
1795112914 40
1795112919 40
```
</details>

---

