---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-14 11:42:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1776180921 32
1776180926 32
1776180931 32
1776180936 32
1776180941 32
1776180946 30
1776180951 30
1776180956 32
1776180961 32
1776180966 32
1776180971 32
1776180976 32
1776180981 32
1776180986 32
1776180991 32
1776180996 32
1776181001 32
1776181006 32
1776181011 32
1776181016 32
```
</details>

---

