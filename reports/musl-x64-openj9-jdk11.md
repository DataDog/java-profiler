---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-15 05:47:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 939 |
| Sample Rate | 15.65/sec |
| Health Score | 978% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 38-58 cores)</summary>

```
1786786947 58
1786786952 58
1786786957 58
1786786962 58
1786786967 58
1786786972 58
1786786977 58
1786786982 58
1786786987 58
1786786992 58
1786786997 58
1786787002 58
1786787007 38
1786787012 38
1786787017 38
1786787022 38
1786787027 38
1786787032 38
1786787037 38
1786787042 38
```
</details>

---

