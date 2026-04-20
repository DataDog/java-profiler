---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-20 07:58:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 34-38 cores)</summary>

```
1776686028 37
1776686033 37
1776686038 37
1776686043 37
1776686048 38
1776686053 38
1776686058 38
1776686063 38
1776686068 38
1776686073 38
1776686078 34
1776686083 34
1776686088 34
1776686093 34
1776686098 34
1776686103 34
1776686108 34
1776686113 34
1776686118 34
1776686123 34
```
</details>

---

