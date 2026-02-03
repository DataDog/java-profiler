---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:38:42 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1770125678 29
1770125683 29
1770125688 29
1770125693 29
1770125698 29
1770125703 29
1770125708 29
1770125713 29
1770125718 29
1770125723 29
1770125728 27
1770125733 27
1770125738 27
1770125743 27
1770125748 27
1770125753 27
1770125758 27
1770125763 27
1770125768 27
1770125773 27
```
</details>

---

