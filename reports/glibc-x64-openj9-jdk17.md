---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 17:15:33 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (5 unique values: 62-80 cores)</summary>

```
1777324025 62
1777324030 62
1777324035 62
1777324040 67
1777324045 67
1777324050 67
1777324055 67
1777324060 67
1777324065 67
1777324070 72
1777324075 72
1777324080 72
1777324085 80
1777324090 80
1777324095 80
1777324100 80
1777324105 80
1777324110 80
1777324115 80
1777324120 80
```
</details>

---

