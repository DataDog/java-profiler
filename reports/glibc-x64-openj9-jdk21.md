---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-16 08:50:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 11 |
| Allocations | 415 |

<details>
<summary>CPU Timeline (7 unique values: 74-90 cores)</summary>

```
1776343500 76
1776343505 76
1776343510 74
1776343515 74
1776343520 78
1776343525 78
1776343530 78
1776343535 85
1776343540 85
1776343545 83
1776343550 83
1776343555 83
1776343560 83
1776343565 83
1776343570 85
1776343575 85
1776343580 87
1776343585 87
1776343590 87
1776343595 85
```
</details>

---

