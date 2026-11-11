---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 18:20:12 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794438919 32
1794438924 32
1794438929 32
1794438934 32
1794438939 32
1794438944 32
1794438949 32
1794438954 32
1794438959 32
1794438964 32
1794438969 32
1794438974 32
1794438979 32
1794438984 32
1794438989 32
1794438994 32
1794438999 32
1794439004 32
1794439009 32
1794439014 32
```
</details>

---

