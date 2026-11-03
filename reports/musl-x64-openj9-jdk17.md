---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:51:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 39-43 cores)</summary>

```
1793727932 39
1793727937 41
1793727942 41
1793727947 41
1793727952 41
1793727957 41
1793727962 41
1793727967 43
1793727972 43
1793727977 43
1793727982 43
1793727987 43
1793727992 43
1793727997 43
1793728002 43
1793728007 43
1793728012 43
1793728017 43
1793728022 43
1793728027 43
```
</details>

---

