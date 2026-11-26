---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 48-55 cores)</summary>

```
1795706024 48
1795706029 48
1795706034 53
1795706039 53
1795706044 53
1795706049 53
1795706054 55
1795706059 55
1795706064 55
1795706069 55
1795706074 55
1795706079 55
1795706084 55
1795706089 55
1795706094 55
1795706099 55
1795706104 55
1795706109 55
1795706114 55
1795706119 55
```
</details>

---

