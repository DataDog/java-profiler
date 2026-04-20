---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-20 06:22:58 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 24-28 cores)</summary>

```
1776680401 24
1776680406 24
1776680411 24
1776680416 24
1776680421 24
1776680426 24
1776680431 24
1776680436 24
1776680441 24
1776680446 24
1776680451 24
1776680456 24
1776680461 28
1776680466 28
1776680471 28
1776680476 28
1776680481 26
1776680486 26
1776680491 26
1776680496 26
```
</details>

---

