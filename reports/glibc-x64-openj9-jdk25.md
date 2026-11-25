---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:45:46 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 10 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 64-68 cores)</summary>

```
1795642916 68
1795642921 68
1795642926 68
1795642931 68
1795642936 68
1795642941 68
1795642946 68
1795642951 68
1795642956 68
1795642961 68
1795642966 68
1795642971 68
1795642976 68
1795642982 68
1795642987 68
1795642992 68
1795642997 68
1795643002 68
1795643007 68
1795643012 68
```
</details>

---

