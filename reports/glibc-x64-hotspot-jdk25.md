---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:50:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 10 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 46-75 cores)</summary>

```
1789738895 49
1789738900 49
1789738905 49
1789738910 49
1789738915 49
1789738920 48
1789738925 48
1789738930 48
1789738935 48
1789738940 46
1789738945 46
1789738950 46
1789738955 54
1789738960 54
1789738965 54
1789738970 54
1789738975 75
1789738980 75
1789738985 75
1789738990 75
```
</details>

---

