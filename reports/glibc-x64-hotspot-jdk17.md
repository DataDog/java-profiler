---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 07:58:12 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 311 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 89-92 cores)</summary>

```
1776686044 91
1776686049 91
1776686054 91
1776686059 91
1776686064 89
1776686069 89
1776686074 89
1776686079 89
1776686084 92
1776686089 92
1776686094 92
1776686099 92
1776686104 92
1776686109 92
1776686114 92
1776686119 92
1776686124 91
1776686129 91
1776686134 91
1776686139 91
```
</details>

---

