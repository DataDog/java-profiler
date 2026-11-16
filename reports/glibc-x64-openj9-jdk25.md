---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 05:18:22 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 83-92 cores)</summary>

```
1794823876 92
1794823881 92
1794823886 92
1794823891 90
1794823896 90
1794823901 90
1794823906 83
1794823911 83
1794823916 83
1794823921 83
1794823926 83
1794823931 83
1794823936 85
1794823941 85
1794823946 87
1794823951 87
1794823956 87
1794823961 87
1794823966 87
1794823971 85
```
</details>

---

