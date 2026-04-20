---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-19 21:17:21 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (4 unique values: 20-25 cores)</summary>

```
1776647559 22
1776647564 22
1776647569 22
1776647574 22
1776647579 22
1776647584 22
1776647589 22
1776647594 22
1776647599 20
1776647604 20
1776647609 20
1776647614 20
1776647619 20
1776647624 20
1776647629 20
1776647634 20
1776647639 20
1776647644 20
1776647649 20
1776647654 20
```
</details>

---

