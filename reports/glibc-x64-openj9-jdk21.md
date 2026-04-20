---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:34:19 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 20-27 cores)</summary>

```
1776695071 27
1776695076 27
1776695081 27
1776695086 27
1776695091 27
1776695096 27
1776695101 27
1776695106 27
1776695111 27
1776695116 27
1776695121 22
1776695126 22
1776695131 22
1776695136 22
1776695141 22
1776695146 22
1776695151 22
1776695156 22
1776695161 22
1776695166 22
```
</details>

---

