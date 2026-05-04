---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:21:05 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 45-64 cores)</summary>

```
1777857385 45
1777857390 45
1777857395 45
1777857400 45
1777857405 45
1777857410 64
1777857415 64
1777857420 64
1777857425 64
1777857430 64
1777857435 64
1777857440 64
1777857445 64
1777857450 64
1777857455 64
1777857460 64
1777857465 64
1777857470 64
1777857475 64
1777857480 64
```
</details>

---

