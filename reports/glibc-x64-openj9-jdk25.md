---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 13:00:29 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 14 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 68-78 cores)</summary>

```
1772819682 68
1772819687 78
1772819692 78
1772819697 77
1772819702 77
1772819707 77
1772819712 77
1772819717 77
1772819722 77
1772819727 77
1772819732 77
1772819737 78
1772819742 78
1772819747 78
1772819752 76
1772819757 76
1772819762 76
1772819767 76
1772819772 76
1772819777 76
```
</details>

---

