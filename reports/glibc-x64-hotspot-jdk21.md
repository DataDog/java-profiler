---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-21 10:43:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 12 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 46-77 cores)</summary>

```
1776782078 55
1776782083 50
1776782088 50
1776782093 46
1776782098 46
1776782103 46
1776782108 46
1776782114 46
1776782119 46
1776782124 46
1776782129 46
1776782134 77
1776782139 77
1776782144 77
1776782149 77
1776782154 77
1776782159 77
1776782164 77
1776782169 77
1776782174 77
```
</details>

---

