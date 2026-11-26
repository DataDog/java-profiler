---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:49:39 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (4 unique values: 41-65 cores)</summary>

```
1795707905 44
1795707910 44
1795707915 44
1795707920 44
1795707925 44
1795707930 44
1795707935 44
1795707940 46
1795707945 46
1795707950 46
1795707955 46
1795707960 46
1795707965 65
1795707970 65
1795707975 41
1795707980 41
1795707985 41
1795707990 41
1795707995 41
1795708000 41
```
</details>

---

