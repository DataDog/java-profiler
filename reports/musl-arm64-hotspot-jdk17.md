---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:38:32 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 13 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 46-56 cores)</summary>

```
1786376024 56
1786376029 56
1786376034 51
1786376039 51
1786376044 51
1786376049 51
1786376054 51
1786376059 46
1786376064 46
1786376069 46
1786376074 46
1786376079 46
1786376084 46
1786376089 46
1786376094 51
1786376099 51
1786376104 51
1786376109 51
1786376114 51
1786376119 56
```
</details>

---

