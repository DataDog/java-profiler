---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-17 11:46:55 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 77-91 cores)</summary>

```
1776440595 77
1776440600 77
1776440605 77
1776440610 77
1776440615 77
1776440620 82
1776440625 82
1776440630 82
1776440635 82
1776440640 82
1776440645 82
1776440650 82
1776440655 82
1776440660 82
1776440665 82
1776440670 82
1776440675 82
1776440680 82
1776440685 86
1776440690 86
```
</details>

---

