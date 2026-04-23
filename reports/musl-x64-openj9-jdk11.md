---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 15:21:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 933 |
| Sample Rate | 15.55/sec |
| Health Score | 972% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 46-63 cores)</summary>

```
1776971694 46
1776971699 49
1776971704 49
1776971709 49
1776971714 49
1776971719 51
1776971724 51
1776971729 51
1776971734 51
1776971739 51
1776971744 51
1776971749 55
1776971754 55
1776971759 55
1776971764 55
1776971769 55
1776971774 55
1776971779 55
1776971784 55
1776971789 55
```
</details>

---

