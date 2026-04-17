---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-17 10:21:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 72-84 cores)</summary>

```
1776435099 74
1776435104 72
1776435109 72
1776435114 74
1776435119 74
1776435124 74
1776435129 74
1776435134 74
1776435139 74
1776435144 74
1776435149 74
1776435154 74
1776435159 74
1776435164 74
1776435169 76
1776435174 76
1776435179 76
1776435185 76
1776435190 76
1776435195 76
```
</details>

---

