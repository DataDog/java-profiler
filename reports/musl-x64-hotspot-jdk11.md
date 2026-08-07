---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 05:50:46 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 89-94 cores)</summary>

```
1786095954 89
1786095959 89
1786095964 91
1786095969 91
1786095974 91
1786095979 91
1786095984 91
1786095989 91
1786095994 91
1786095999 91
1786096004 94
1786096009 94
1786096014 94
1786096019 94
1786096024 94
1786096029 94
1786096034 94
1786096039 94
1786096044 94
1786096049 94
```
</details>

---

