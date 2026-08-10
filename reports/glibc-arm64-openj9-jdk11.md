---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 05:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 7 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 12 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786354974 48
1786354979 48
1786354984 48
1786354989 48
1786354994 48
1786354999 48
1786355004 48
1786355009 48
1786355014 53
1786355019 53
1786355024 53
1786355029 53
1786355034 53
1786355039 53
1786355044 53
1786355049 53
1786355054 53
1786355059 53
1786355064 53
1786355069 53
```
</details>

---

