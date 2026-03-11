---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-11 10:47:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1773240068 26
1773240073 26
1773240078 26
1773240083 26
1773240088 26
1773240093 26
1773240098 32
1773240103 32
1773240108 29
1773240113 29
1773240118 29
1773240123 29
1773240128 29
1773240133 29
1773240138 29
1773240143 29
1773240148 29
1773240153 29
1773240158 29
1773240163 29
```
</details>

---

