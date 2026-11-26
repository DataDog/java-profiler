---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 05:52:47 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 10 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (6 unique values: 59-74 cores)</summary>

```
1795690053 72
1795690058 72
1795690064 74
1795690069 74
1795690074 74
1795690079 65
1795690084 65
1795690089 65
1795690094 65
1795690099 63
1795690104 63
1795690109 63
1795690114 63
1795690119 63
1795690124 66
1795690129 66
1795690134 59
1795690139 59
1795690144 59
1795690149 59
```
</details>

---

