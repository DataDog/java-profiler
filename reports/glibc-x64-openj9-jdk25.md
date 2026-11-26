---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:18:50 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1795706034 64
1795706039 64
1795706044 64
1795706049 64
1795706054 64
1795706059 64
1795706064 64
1795706069 64
1795706074 66
1795706079 66
1795706084 66
1795706089 66
1795706094 66
1795706099 66
1795706104 66
1795706109 66
1795706114 66
1795706119 66
1795706124 66
1795706129 66
```
</details>

---

