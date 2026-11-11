---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:04:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 70-73 cores)</summary>

```
1794430799 70
1794430804 70
1794430809 70
1794430814 70
1794430819 70
1794430824 70
1794430829 70
1794430834 70
1794430839 73
1794430844 73
1794430849 73
1794430854 73
1794430859 73
1794430864 73
1794430869 73
1794430874 73
1794430879 73
1794430884 73
1794430889 73
1794430894 73
```
</details>

---

