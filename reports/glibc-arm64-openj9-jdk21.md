---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 06:28:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 19-52 cores)</summary>

```
1793355874 19
1793355879 19
1793355884 19
1793355889 19
1793355894 19
1793355899 19
1793355904 19
1793355909 19
1793355914 19
1793355919 19
1793355924 19
1793355929 19
1793355934 23
1793355939 23
1793355944 23
1793355949 23
1793355954 23
1793355959 31
1793355964 31
1793355969 31
```
</details>

---

