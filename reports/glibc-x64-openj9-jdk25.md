---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 10:05:06 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 55-61 cores)</summary>

```
1776693693 57
1776693698 57
1776693703 61
1776693708 61
1776693713 56
1776693718 56
1776693723 56
1776693728 56
1776693733 56
1776693738 56
1776693743 56
1776693748 56
1776693753 56
1776693758 56
1776693763 56
1776693768 60
1776693773 60
1776693778 60
1776693783 60
1776693788 60
```
</details>

---

