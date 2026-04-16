---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-16 12:01:42 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 73-93 cores)</summary>

```
1776355073 73
1776355078 73
1776355083 73
1776355088 83
1776355093 83
1776355098 83
1776355103 83
1776355108 88
1776355113 88
1776355118 88
1776355123 88
1776355128 88
1776355133 88
1776355138 88
1776355143 93
1776355148 93
1776355153 93
1776355158 93
1776355163 93
1776355168 93
```
</details>

---

