---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:51:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1793727949 46
1793727954 46
1793727959 46
1793727964 46
1793727969 46
1793727974 46
1793727979 46
1793727984 46
1793727990 46
1793727995 46
1793728000 46
1793728005 46
1793728010 46
1793728015 46
1793728020 48
1793728025 48
1793728030 36
1793728035 36
1793728040 36
1793728045 36
```
</details>

---

