---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-17 10:21:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 10 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 50-55 cores)</summary>

```
1776435089 51
1776435094 51
1776435099 51
1776435104 51
1776435109 51
1776435114 51
1776435119 51
1776435125 51
1776435130 51
1776435135 51
1776435140 51
1776435145 53
1776435150 53
1776435155 55
1776435160 55
1776435165 55
1776435170 55
1776435175 55
1776435180 55
1776435185 50
```
</details>

---

