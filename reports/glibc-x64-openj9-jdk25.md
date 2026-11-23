---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 08:37:36 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 49-54 cores)</summary>

```
1795440805 54
1795440810 54
1795440815 54
1795440820 54
1795440825 49
1795440830 49
1795440835 49
1795440840 49
1795440845 52
1795440850 52
1795440855 52
1795440860 52
1795440865 52
1795440870 52
1795440875 52
1795440880 52
1795440885 52
1795440890 52
1795440895 52
1795440900 52
```
</details>

---

