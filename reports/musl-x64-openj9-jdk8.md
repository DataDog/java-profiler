---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 10:08:12 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 55-64 cores)</summary>

```
1795618871 64
1795618876 64
1795618881 64
1795618886 64
1795618891 64
1795618896 64
1795618901 64
1795618906 64
1795618911 64
1795618916 64
1795618922 64
1795618927 64
1795618932 64
1795618937 64
1795618942 64
1795618947 64
1795618952 64
1795618957 64
1795618962 64
1795618967 64
```
</details>

---

