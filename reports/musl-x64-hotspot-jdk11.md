---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 05:55:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 71-75 cores)</summary>

```
1793703018 73
1793703023 73
1793703029 73
1793703034 73
1793703039 73
1793703044 73
1793703049 73
1793703054 73
1793703059 73
1793703064 73
1793703069 73
1793703074 73
1793703079 73
1793703084 75
1793703089 75
1793703094 73
1793703099 73
1793703104 73
1793703109 73
1793703114 73
```
</details>

---

