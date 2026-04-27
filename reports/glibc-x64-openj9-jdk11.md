---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 17:15:32 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 927 |
| Sample Rate | 15.45/sec |
| Health Score | 966% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 52-56 cores)</summary>

```
1777324060 56
1777324065 56
1777324070 56
1777324075 56
1777324080 56
1777324085 56
1777324090 56
1777324095 56
1777324100 56
1777324105 56
1777324110 56
1777324115 56
1777324120 56
1777324125 56
1777324130 56
1777324135 56
1777324140 52
1777324145 52
1777324150 52
1777324155 52
```
</details>

---

