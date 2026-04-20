---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 07:58:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 41-51 cores)</summary>

```
1776686055 41
1776686060 41
1776686065 41
1776686070 51
1776686075 51
1776686080 51
1776686085 51
1776686090 51
1776686095 51
1776686100 51
1776686105 51
1776686110 51
1776686115 51
1776686120 51
1776686125 51
1776686130 51
1776686135 51
1776686140 51
1776686145 51
1776686150 51
```
</details>

---

