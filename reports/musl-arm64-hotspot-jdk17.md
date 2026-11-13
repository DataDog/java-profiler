---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 12:19:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 11 |
| Allocations | 120 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794590054 43
1794590059 43
1794590064 43
1794590069 43
1794590074 43
1794590079 43
1794590084 46
1794590089 46
1794590094 46
1794590099 46
1794590104 46
1794590109 46
1794590114 46
1794590119 46
1794590124 48
1794590129 48
1794590134 48
1794590139 48
1794590144 48
1794590149 48
```
</details>

---

