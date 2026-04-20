---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-19 21:19:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1776647649 59
1776647654 59
1776647659 59
1776647664 59
1776647669 54
1776647674 54
1776647679 54
1776647684 54
1776647689 54
1776647694 54
1776647699 54
1776647704 54
1776647709 54
1776647714 54
1776647719 54
1776647724 54
1776647729 54
1776647734 54
1776647739 54
1776647744 54
```
</details>

---

