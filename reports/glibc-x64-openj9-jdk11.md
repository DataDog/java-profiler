---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 13:20:44 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1792602524 44
1792602529 44
1792602534 44
1792602539 44
1792602544 44
1792602549 46
1792602554 46
1792602559 46
1792602565 46
1792602570 46
1792602575 46
1792602580 46
1792602585 46
1792602590 46
1792602595 46
1792602600 46
1792602605 46
1792602610 46
1792602615 46
1792602620 46
```
</details>

---

