---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:51:39 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 76-81 cores)</summary>

```
1793727959 76
1793727964 76
1793727969 76
1793727974 76
1793727979 76
1793727984 76
1793727989 76
1793727994 76
1793727999 76
1793728004 76
1793728009 76
1793728014 76
1793728019 78
1793728024 78
1793728029 78
1793728034 78
1793728039 78
1793728044 78
1793728049 78
1793728054 78
```
</details>

---

