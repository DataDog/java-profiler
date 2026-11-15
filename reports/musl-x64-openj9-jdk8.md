---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-15 18:26:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 51-73 cores)</summary>

```
1794784886 53
1794784891 53
1794784896 53
1794784901 51
1794784906 51
1794784911 51
1794784916 51
1794784921 51
1794784926 51
1794784931 51
1794784936 51
1794784941 72
1794784946 72
1794784951 70
1794784956 70
1794784961 70
1794784966 73
1794784971 73
1794784976 73
1794784981 73
```
</details>

---

