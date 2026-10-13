---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 13:24:02 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
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
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 76-86 cores)</summary>

```
1791911871 82
1791911876 82
1791911881 82
1791911886 82
1791911891 82
1791911896 84
1791911901 84
1791911906 84
1791911911 82
1791911916 82
1791911921 82
1791911926 82
1791911931 78
1791911936 78
1791911941 78
1791911946 78
1791911951 76
1791911956 76
1791911962 78
1791911967 78
```
</details>

---

