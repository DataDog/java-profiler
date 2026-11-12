---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:40:44 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 45-71 cores)</summary>

```
1794504872 45
1794504877 45
1794504882 45
1794504887 45
1794504892 45
1794504897 45
1794504902 45
1794504907 45
1794504912 45
1794504917 45
1794504922 45
1794504927 45
1794504932 49
1794504937 49
1794504942 49
1794504947 49
1794504952 71
1794504957 71
1794504962 71
1794504967 71
```
</details>

---

