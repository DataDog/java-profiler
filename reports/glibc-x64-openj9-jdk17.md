---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:51:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 73-77 cores)</summary>

```
1793727962 75
1793727967 75
1793727972 73
1793727977 73
1793727982 73
1793727987 73
1793727992 73
1793727997 73
1793728002 77
1793728007 77
1793728012 77
1793728017 77
1793728023 77
1793728028 77
1793728033 77
1793728038 77
1793728043 77
1793728048 77
1793728053 77
1793728058 77
```
</details>

---

