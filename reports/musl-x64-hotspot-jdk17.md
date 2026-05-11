---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-11 10:05:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 928 |
| Sample Rate | 15.47/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 74-81 cores)</summary>

```
1778507978 80
1778507983 80
1778507988 80
1778507993 80
1778507998 76
1778508003 76
1778508008 76
1778508013 76
1778508018 76
1778508023 76
1778508028 74
1778508033 74
1778508038 74
1778508043 74
1778508048 74
1778508053 74
1778508058 74
1778508063 74
1778508068 74
1778508073 74
```
</details>

---

