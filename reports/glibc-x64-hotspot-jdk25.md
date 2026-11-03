---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 05:55:12 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 10 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1793703057 56
1793703062 56
1793703067 56
1793703072 56
1793703077 56
1793703082 56
1793703087 56
1793703092 56
1793703097 56
1793703102 56
1793703107 56
1793703112 56
1793703117 56
1793703122 58
1793703127 58
1793703132 58
1793703137 58
1793703142 58
1793703147 58
1793703152 58
```
</details>

---

