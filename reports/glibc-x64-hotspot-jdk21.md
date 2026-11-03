---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 12:51:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (5 unique values: 46-66 cores)</summary>

```
1793727984 56
1793727989 56
1793727994 56
1793727999 56
1793728004 56
1793728009 56
1793728014 56
1793728019 56
1793728024 56
1793728029 56
1793728034 48
1793728039 48
1793728044 48
1793728049 48
1793728054 48
1793728059 48
1793728064 48
1793728069 48
1793728074 46
1793728079 46
```
</details>

---

