---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:02:40 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 50-57 cores)</summary>

```
1795618642 50
1795618647 50
1795618652 50
1795618657 50
1795618662 50
1795618667 50
1795618672 50
1795618677 50
1795618682 50
1795618687 50
1795618692 50
1795618697 50
1795618702 50
1795618707 51
1795618712 51
1795618717 51
1795618722 51
1795618727 51
1795618732 51
1795618737 51
```
</details>

---

