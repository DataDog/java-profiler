---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-05 13:29:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (2 unique values: 24-28 cores)</summary>

```
1772735109 28
1772735114 28
1772735119 28
1772735124 28
1772735129 28
1772735134 28
1772735139 28
1772735144 28
1772735149 28
1772735154 28
1772735159 28
1772735164 28
1772735169 28
1772735174 28
1772735179 28
1772735184 28
1772735189 24
1772735194 24
1772735199 24
1772735204 24
```
</details>

---

