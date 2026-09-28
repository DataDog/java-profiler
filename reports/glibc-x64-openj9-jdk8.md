---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-28 06:45:42 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1790592047 53
1790592053 53
1790592058 53
1790592063 53
1790592068 53
1790592073 53
1790592078 53
1790592083 55
1790592088 55
1790592093 55
1790592098 55
1790592103 55
1790592108 55
1790592113 55
1790592118 55
1790592123 55
1790592128 55
1790592133 55
1790592138 55
1790592143 55
```
</details>

---

