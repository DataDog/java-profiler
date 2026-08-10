---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 11:38:33 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786376049 30
1786376054 30
1786376059 30
1786376064 30
1786376069 30
1786376074 30
1786376079 30
1786376084 30
1786376089 30
1786376094 30
1786376099 30
1786376104 32
1786376109 32
1786376114 32
1786376119 32
1786376124 32
1786376129 32
1786376134 32
1786376139 32
1786376144 32
```
</details>

---

