---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 04:41:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 12 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 12 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1794389862 57
1794389867 57
1794389872 57
1794389877 57
1794389882 57
1794389887 59
1794389892 59
1794389897 59
1794389902 59
1794389907 59
1794389912 59
1794389917 59
1794389922 59
1794389927 59
1794389932 59
1794389937 59
1794389942 59
1794389947 59
1794389952 59
1794389957 59
```
</details>

---

