---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 11:57:51 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (4 unique values: 80-88 cores)</summary>

```
1776700042 80
1776700047 80
1776700052 80
1776700057 82
1776700062 82
1776700067 82
1776700072 82
1776700077 82
1776700082 88
1776700087 88
1776700092 88
1776700097 88
1776700102 88
1776700107 88
1776700112 88
1776700117 88
1776700122 88
1776700127 88
1776700132 88
1776700137 88
```
</details>

---

