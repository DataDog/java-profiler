---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-15 05:47:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786786982 46
1786786987 46
1786786992 46
1786786997 46
1786787002 46
1786787007 46
1786787012 46
1786787017 46
1786787022 46
1786787027 46
1786787032 46
1786787037 48
1786787042 48
1786787047 48
1786787052 48
1786787057 48
1786787062 48
1786787067 48
1786787072 48
1786787077 48
```
</details>

---

