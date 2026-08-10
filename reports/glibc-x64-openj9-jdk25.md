---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 15:31:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 89-94 cores)</summary>

```
1786389973 91
1786389978 91
1786389984 91
1786389989 91
1786389994 91
1786389999 91
1786390004 89
1786390009 89
1786390014 89
1786390019 92
1786390024 92
1786390029 92
1786390034 92
1786390039 92
1786390044 92
1786390049 92
1786390054 94
1786390059 94
1786390064 94
1786390069 94
```
</details>

---

