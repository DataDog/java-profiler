---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 12:51:45 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 42-51 cores)</summary>

```
1770140857 51
1770140862 51
1770140867 42
1770140872 42
1770140877 42
1770140882 42
1770140887 42
1770140892 42
1770140897 42
1770140902 42
1770140907 42
1770140912 42
1770140917 42
1770140922 42
1770140927 42
1770140932 42
1770140937 42
1770140942 42
1770140947 42
1770140952 42
```
</details>

---

