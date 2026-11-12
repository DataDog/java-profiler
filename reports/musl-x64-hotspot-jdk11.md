---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:07:10 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (5 unique values: 57-94 cores)</summary>

```
1794502910 94
1794502915 94
1794502920 94
1794502925 94
1794502930 78
1794502935 78
1794502940 78
1794502945 78
1794502950 78
1794502955 78
1794502960 78
1794502965 75
1794502970 75
1794502975 75
1794502980 75
1794502985 75
1794502990 75
1794502995 75
1794503000 75
1794503005 75
```
</details>

---

