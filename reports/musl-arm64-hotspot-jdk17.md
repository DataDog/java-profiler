---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-15 20:41:35 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 11 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 13 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (4 unique values: 19-26 cores)</summary>

```
1794793054 26
1794793059 26
1794793064 26
1794793069 26
1794793074 26
1794793079 26
1794793084 24
1794793089 24
1794793094 24
1794793099 24
1794793104 19
1794793109 19
1794793114 19
1794793119 19
1794793124 19
1794793129 21
1794793134 21
1794793139 21
1794793144 21
1794793149 21
```
</details>

---

