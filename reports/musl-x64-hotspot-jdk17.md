---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 07:24:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 19-25 cores)</summary>

```
1776252028 19
1776252033 19
1776252038 19
1776252043 19
1776252048 19
1776252053 19
1776252058 19
1776252063 19
1776252068 24
1776252073 24
1776252078 22
1776252083 22
1776252088 22
1776252093 22
1776252098 22
1776252103 22
1776252108 25
1776252113 25
1776252118 25
1776252123 23
```
</details>

---

