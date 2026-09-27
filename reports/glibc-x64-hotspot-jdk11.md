---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-27 00:58:57 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 995 |
| Sample Rate | 16.58/sec |
| Health Score | 1036% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1790484804 47
1790484809 47
1790484814 49
1790484819 49
1790484824 49
1790484829 49
1790484834 49
1790484839 49
1790484844 49
1790484849 49
1790484854 49
1790484859 49
1790484864 49
1790484869 49
1790484874 49
1790484879 49
1790484884 49
1790484889 49
1790484894 49
1790484899 49
```
</details>

---

