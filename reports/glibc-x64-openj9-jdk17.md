---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 09:46:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 72-94 cores)</summary>

```
1794580915 74
1794580920 74
1794580925 72
1794580930 72
1794580935 72
1794580940 72
1794580945 72
1794580950 72
1794580955 72
1794580960 72
1794580965 72
1794580970 72
1794580975 72
1794580980 72
1794580985 72
1794580990 72
1794580995 94
1794581000 94
1794581005 94
1794581010 94
```
</details>

---

