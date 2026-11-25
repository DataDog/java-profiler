---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:45:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 68-72 cores)</summary>

```
1795642879 68
1795642884 68
1795642889 68
1795642894 68
1795642899 68
1795642904 68
1795642909 68
1795642914 70
1795642919 70
1795642924 70
1795642929 70
1795642934 70
1795642939 70
1795642944 70
1795642949 70
1795642954 70
1795642959 70
1795642964 70
1795642969 70
1795642974 72
```
</details>

---

