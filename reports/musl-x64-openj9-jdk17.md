---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:07:10 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 10 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 10 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (2 unique values: 85-90 cores)</summary>

```
1794502896 90
1794502901 90
1794502906 90
1794502911 90
1794502916 90
1794502921 90
1794502926 85
1794502931 85
1794502936 85
1794502941 85
1794502946 85
1794502951 85
1794502956 85
1794502961 85
1794502966 85
1794502971 85
1794502976 85
1794502981 85
1794502986 85
1794502991 85
```
</details>

---

