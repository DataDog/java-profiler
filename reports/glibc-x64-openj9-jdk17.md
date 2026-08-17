---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-17 09:18:30 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1786972407 96
1786972412 96
1786972417 96
1786972422 96
1786972427 88
1786972432 88
1786972437 88
1786972442 88
1786972447 88
1786972452 88
1786972457 88
1786972462 88
1786972467 88
1786972472 88
1786972477 88
1786972482 88
1786972487 88
1786972492 88
1786972497 88
1786972502 88
```
</details>

---

