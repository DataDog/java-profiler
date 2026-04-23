---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 06:56:15 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 896 |
| Sample Rate | 14.93/sec |
| Health Score | 933% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 57-64 cores)</summary>

```
1776941470 64
1776941475 64
1776941480 64
1776941485 64
1776941490 57
1776941495 57
1776941500 59
1776941505 59
1776941510 59
1776941515 59
1776941520 59
1776941525 59
1776941530 59
1776941535 59
1776941540 59
1776941545 57
1776941550 57
1776941555 57
1776941560 61
1776941565 61
```
</details>

---

