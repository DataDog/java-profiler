---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 12:51:39 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 50-54 cores)</summary>

```
1793727952 52
1793727957 52
1793727962 50
1793727967 50
1793727972 50
1793727977 50
1793727982 52
1793727987 52
1793727992 52
1793727997 52
1793728002 52
1793728007 54
1793728012 54
1793728017 54
1793728022 54
1793728027 54
1793728032 54
1793728037 54
1793728042 54
1793728047 54
```
</details>

---

