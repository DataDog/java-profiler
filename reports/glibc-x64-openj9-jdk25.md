---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-28 18:13:25 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 45-78 cores)</summary>

```
1777413972 78
1777413977 78
1777413982 78
1777413987 78
1777413992 78
1777413997 78
1777414002 54
1777414007 54
1777414012 54
1777414017 54
1777414022 54
1777414027 54
1777414032 54
1777414037 45
1777414042 45
1777414047 45
1777414052 45
1777414057 45
1777414062 45
1777414067 45
```
</details>

---

