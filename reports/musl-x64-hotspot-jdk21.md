---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-14 09:58:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 22-30 cores)</summary>

```
1791985995 26
1791986000 26
1791986005 26
1791986010 28
1791986015 28
1791986020 28
1791986025 28
1791986030 28
1791986035 28
1791986040 28
1791986045 30
1791986050 30
1791986055 30
1791986060 30
1791986065 27
1791986070 27
1791986075 27
1791986080 27
1791986085 27
1791986090 27
```
</details>

---

