---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-15 05:47:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 33-35 cores)</summary>

```
1786786962 33
1786786967 33
1786786972 33
1786786977 33
1786786982 35
1786786987 35
1786786992 35
1786786997 35
1786787002 35
1786787007 35
1786787012 35
1786787017 35
1786787022 35
1786787027 35
1786787032 35
1786787037 35
1786787042 35
1786787047 35
1786787052 35
1786787057 35
```
</details>

---

