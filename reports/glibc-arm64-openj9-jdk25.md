---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 07:58:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776686070 64
1776686075 64
1776686080 64
1776686085 64
1776686090 64
1776686095 64
1776686100 64
1776686105 64
1776686110 64
1776686115 64
1776686120 64
1776686125 59
1776686130 59
1776686135 59
1776686140 59
1776686145 59
1776686150 59
1776686155 59
1776686160 59
1776686165 59
```
</details>

---

