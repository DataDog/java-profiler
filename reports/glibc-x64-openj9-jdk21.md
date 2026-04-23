---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 12:53:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 18-23 cores)</summary>

```
1776962902 23
1776962907 23
1776962912 23
1776962917 23
1776962922 23
1776962927 23
1776962932 23
1776962937 23
1776962942 23
1776962947 23
1776962952 23
1776962957 23
1776962962 23
1776962967 23
1776962972 23
1776962977 23
1776962982 18
1776962987 18
1776962992 18
1776962997 18
```
</details>

---

