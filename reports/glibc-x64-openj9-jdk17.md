---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-15 19:49:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 71-79 cores)</summary>

```
1794789897 79
1794789902 79
1794789907 79
1794789912 79
1794789917 79
1794789922 79
1794789927 79
1794789932 79
1794789937 79
1794789942 79
1794789947 79
1794789952 79
1794789957 71
1794789962 71
1794789967 71
1794789972 71
1794789977 73
1794789982 73
1794789987 73
1794789992 73
```
</details>

---

