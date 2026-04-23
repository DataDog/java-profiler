---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 15:03:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 34-77 cores)</summary>

```
1776970643 34
1776970648 34
1776970653 34
1776970658 34
1776970663 34
1776970668 34
1776970673 34
1776970678 34
1776970683 34
1776970688 37
1776970693 37
1776970698 37
1776970703 37
1776970708 37
1776970713 37
1776970718 37
1776970723 37
1776970728 73
1776970733 73
1776970738 73
```
</details>

---

