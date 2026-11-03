---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:51:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793727963 48
1793727968 48
1793727973 48
1793727978 48
1793727983 48
1793727988 48
1793727993 48
1793727998 48
1793728004 48
1793728009 48
1793728014 48
1793728019 48
1793728024 48
1793728029 48
1793728034 48
1793728039 48
1793728044 48
1793728049 48
1793728054 48
1793728059 48
```
</details>

---

