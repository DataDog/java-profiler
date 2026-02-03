---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 12:51:45 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1770140867 32
1770140872 32
1770140877 32
1770140882 32
1770140887 32
1770140892 32
1770140897 32
1770140902 32
1770140907 32
1770140912 32
1770140917 32
1770140922 32
1770140927 32
1770140932 32
1770140937 32
1770140942 32
1770140947 28
1770140952 28
1770140957 28
1770140962 28
```
</details>

---

