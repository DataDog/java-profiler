---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 07:06:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 62-76 cores)</summary>

```
1790074864 62
1790074869 62
1790074874 62
1790074879 62
1790074884 62
1790074889 64
1790074894 64
1790074899 66
1790074904 66
1790074909 76
1790074914 76
1790074919 74
1790074924 74
1790074929 74
1790074934 74
1790074939 74
1790074944 74
1790074949 74
1790074954 74
1790074959 74
```
</details>

---

