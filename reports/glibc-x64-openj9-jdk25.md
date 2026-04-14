---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-14 06:19:14 EDT

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
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 78-96 cores)</summary>

```
1776161584 96
1776161589 96
1776161594 96
1776161599 96
1776161604 96
1776161609 96
1776161614 96
1776161619 96
1776161624 96
1776161629 78
1776161634 78
1776161639 78
1776161644 78
1776161649 78
1776161654 78
1776161659 78
1776161664 78
1776161669 78
1776161674 78
1776161679 78
```
</details>

---

