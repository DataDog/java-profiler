---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:34:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1789716503 96
1789716508 96
1789716513 96
1789716518 96
1789716523 96
1789716528 96
1789716533 96
1789716538 96
1789716543 96
1789716548 96
1789716553 96
1789716558 92
1789716563 92
1789716568 92
1789716573 92
1789716578 92
1789716583 92
1789716588 92
1789716593 92
1789716598 94
```
</details>

---

