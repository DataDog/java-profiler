---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-29 12:19:50 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 15.53/sec |
| Health Score | 971% |
| Threads | 10 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 24.80/sec |
| Health Score | 1550% |
| Threads | 12 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 64-88 cores)</summary>

```
1769706844 86
1769706849 86
1769706854 86
1769706859 88
1769706864 88
1769706869 64
1769706874 64
1769706879 64
1769706884 64
1769706889 64
1769706894 64
1769706899 64
1769706904 64
1769706909 64
1769706914 64
1769706919 64
1769706924 64
1769706929 64
1769706934 72
1769706939 72
```
</details>

---

