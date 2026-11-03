---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 12:51:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 348 |
| Sample Rate | 5.80/sec |
| Health Score | 362% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 15-34 cores)</summary>

```
1793727932 15
1793727937 15
1793727942 15
1793727947 15
1793727952 15
1793727957 15
1793727962 15
1793727967 34
1793727972 34
1793727977 17
1793727982 17
1793727987 17
1793727992 17
1793727997 17
1793728002 17
1793728007 17
1793728012 17
1793728017 17
1793728022 17
1793728027 17
```
</details>

---

