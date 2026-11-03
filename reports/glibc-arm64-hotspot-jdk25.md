---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 05:55:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 7 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1793703048 41
1793703053 41
1793703059 41
1793703064 41
1793703069 41
1793703074 41
1793703079 41
1793703084 41
1793703089 41
1793703094 41
1793703099 41
1793703104 41
1793703109 41
1793703114 46
1793703119 46
1793703124 46
1793703129 46
1793703134 46
1793703139 46
1793703144 46
```
</details>

---

