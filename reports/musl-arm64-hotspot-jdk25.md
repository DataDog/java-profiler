---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 00:07:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 13 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 12-17 cores)</summary>

```
1793855024 17
1793855029 17
1793855034 17
1793855039 17
1793855044 17
1793855049 17
1793855054 17
1793855059 17
1793855064 17
1793855069 17
1793855074 17
1793855079 17
1793855084 17
1793855089 17
1793855094 12
1793855099 12
1793855104 12
1793855109 12
1793855114 12
1793855119 12
```
</details>

---

