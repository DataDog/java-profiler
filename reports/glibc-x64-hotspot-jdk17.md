---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 08:11:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 11 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (4 unique values: 70-83 cores)</summary>

```
1794316050 83
1794316055 83
1794316060 83
1794316065 83
1794316070 83
1794316075 83
1794316080 83
1794316085 81
1794316090 81
1794316095 78
1794316100 78
1794316105 78
1794316110 78
1794316115 78
1794316120 78
1794316125 78
1794316130 70
1794316135 70
1794316140 70
1794316145 70
```
</details>

---

