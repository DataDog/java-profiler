---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 05:52:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 5 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1795690054 68
1795690059 68
1795690064 66
1795690069 66
1795690074 66
1795690079 66
1795690084 66
1795690089 66
1795690094 66
1795690099 66
1795690104 66
1795690109 66
1795690114 66
1795690119 66
1795690124 66
1795690129 66
1795690134 66
1795690139 66
1795690144 66
1795690149 66
```
</details>

---

