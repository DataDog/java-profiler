---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 05:59:00 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 61-81 cores)</summary>

```
1794912837 62
1794912842 62
1794912847 62
1794912852 62
1794912857 64
1794912862 64
1794912867 64
1794912872 64
1794912877 64
1794912882 64
1794912887 64
1794912892 64
1794912897 64
1794912902 64
1794912907 64
1794912912 64
1794912917 64
1794912922 64
1794912927 64
1794912932 81
```
</details>

---

