---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-17 10:21:30 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (6 unique values: 86-93 cores)</summary>

```
1776435160 88
1776435165 88
1776435170 88
1776435175 86
1776435180 86
1776435185 86
1776435190 86
1776435195 89
1776435200 89
1776435205 89
1776435210 87
1776435215 87
1776435220 87
1776435225 87
1776435230 89
1776435235 89
1776435240 89
1776435245 91
1776435250 91
1776435255 91
```
</details>

---

