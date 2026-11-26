---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:18:51 EST

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 32 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 59-96 cores)</summary>

```
1795706044 96
1795706049 96
1795706054 96
1795706059 96
1795706064 96
1795706069 96
1795706074 96
1795706079 96
1795706084 96
1795706089 96
1795706094 96
1795706099 96
1795706104 96
1795706109 68
1795706114 68
1795706119 68
1795706124 68
1795706129 68
1795706134 68
1795706139 68
```
</details>

---

