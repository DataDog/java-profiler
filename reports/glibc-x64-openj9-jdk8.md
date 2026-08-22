---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-22 08:14:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 324 |
| Sample Rate | 5.40/sec |
| Health Score | 338% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 57-62 cores)</summary>

```
1787400594 62
1787400599 62
1787400605 62
1787400610 57
1787400615 57
1787400620 57
1787400625 57
1787400630 57
1787400635 57
1787400640 57
1787400645 57
1787400650 57
1787400655 62
1787400660 62
1787400665 62
1787400670 62
1787400675 62
1787400680 62
1787400685 62
1787400690 62
```
</details>

---

