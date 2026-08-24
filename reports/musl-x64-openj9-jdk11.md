---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-24 09:28:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 80-96 cores)</summary>

```
1787577804 80
1787577809 80
1787577814 80
1787577819 80
1787577824 80
1787577829 88
1787577834 88
1787577839 88
1787577844 88
1787577849 88
1787577854 88
1787577859 88
1787577864 88
1787577869 88
1787577874 88
1787577879 88
1787577884 88
1787577889 88
1787577894 88
1787577899 88
```
</details>

---

