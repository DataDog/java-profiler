---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-17 08:06:00 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 59-81 cores)</summary>

```
1776427165 81
1776427170 81
1776427175 81
1776427180 81
1776427185 81
1776427190 81
1776427195 59
1776427200 59
1776427205 59
1776427210 59
1776427215 59
1776427220 59
1776427225 59
1776427230 59
1776427235 59
1776427240 59
1776427245 61
1776427250 61
1776427255 61
1776427260 61
```
</details>

---

