---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 07:16:42 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786446769 48
1786446774 48
1786446779 48
1786446784 46
1786446789 46
1786446794 46
1786446799 46
1786446804 46
1786446809 46
1786446814 46
1786446819 46
1786446824 46
1786446829 46
1786446834 46
1786446839 48
1786446844 48
1786446849 48
1786446854 48
1786446859 48
1786446864 48
```
</details>

---

