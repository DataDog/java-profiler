---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 10:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 53-57 cores)</summary>

```
1795706004 55
1795706009 55
1795706014 57
1795706019 57
1795706024 57
1795706029 57
1795706034 53
1795706039 53
1795706044 53
1795706049 53
1795706054 53
1795706059 53
1795706064 53
1795706069 53
1795706074 53
1795706079 53
1795706084 53
1795706089 53
1795706094 53
1795706099 53
```
</details>

---

