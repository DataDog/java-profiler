---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-24 09:28:57 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787577819 96
1787577824 96
1787577829 96
1787577834 96
1787577839 96
1787577844 96
1787577849 96
1787577854 96
1787577859 96
1787577864 96
1787577869 96
1787577874 94
1787577879 94
1787577884 94
1787577889 94
1787577894 94
1787577899 94
1787577904 94
1787577909 94
1787577914 94
```
</details>

---

