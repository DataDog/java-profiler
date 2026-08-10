---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 01:04:39 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 62-96 cores)</summary>

```
1786337934 96
1786337939 96
1786337944 94
1786337949 94
1786337954 92
1786337959 92
1786337964 92
1786337969 92
1786337974 92
1786337979 92
1786337984 92
1786337989 92
1786337994 92
1786337999 92
1786338004 92
1786338009 92
1786338014 92
1786338019 92
1786338024 92
1786338029 92
```
</details>

---

