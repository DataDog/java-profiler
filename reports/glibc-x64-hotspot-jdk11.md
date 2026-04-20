---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 11:57:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 33-59 cores)</summary>

```
1776699986 35
1776699991 35
1776699996 35
1776700001 35
1776700006 35
1776700011 35
1776700016 35
1776700021 35
1776700026 35
1776700031 35
1776700036 33
1776700041 33
1776700046 59
1776700051 59
1776700056 59
1776700061 39
1776700066 39
1776700071 39
1776700076 39
1776700081 39
```
</details>

---

