---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 03:42:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 9 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1776670381 54
1776670386 54
1776670391 54
1776670396 54
1776670401 54
1776670406 54
1776670411 54
1776670416 54
1776670421 54
1776670426 54
1776670431 54
1776670436 54
1776670441 59
1776670446 59
1776670451 59
1776670456 59
1776670461 59
1776670466 59
1776670471 59
1776670476 59
```
</details>

---

