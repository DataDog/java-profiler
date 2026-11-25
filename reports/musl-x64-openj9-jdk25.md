---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:08:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1795618861 59
1795618866 59
1795618871 59
1795618876 59
1795618881 59
1795618886 59
1795618891 64
1795618897 64
1795618902 64
1795618907 64
1795618912 62
1795618917 62
1795618922 62
1795618927 62
1795618932 62
1795618937 62
1795618942 62
1795618947 62
1795618952 62
1795618957 62
```
</details>

---

