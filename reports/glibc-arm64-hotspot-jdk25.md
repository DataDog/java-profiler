---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 12:51:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793728034 48
1793728039 48
1793728044 48
1793728049 48
1793728054 48
1793728059 48
1793728064 48
1793728069 48
1793728074 48
1793728079 48
1793728084 48
1793728089 48
1793728094 48
1793728099 48
1793728104 48
1793728109 48
1793728114 48
1793728119 43
1793728124 43
1793728129 43
```
</details>

---

