---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-22 14:08:54 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 894 |
| Sample Rate | 14.90/sec |
| Health Score | 931% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (7 unique values: 40-60 cores)</summary>

```
1776881036 40
1776881041 44
1776881046 44
1776881051 44
1776881056 44
1776881061 44
1776881066 44
1776881071 53
1776881076 53
1776881081 53
1776881086 53
1776881091 53
1776881096 53
1776881101 53
1776881106 53
1776881111 53
1776881116 53
1776881121 57
1776881126 57
1776881131 55
```
</details>

---

