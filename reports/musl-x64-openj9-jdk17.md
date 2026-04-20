---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-19 21:19:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 50-60 cores)</summary>

```
1776647624 50
1776647629 50
1776647634 50
1776647639 50
1776647644 50
1776647649 50
1776647654 50
1776647659 50
1776647664 50
1776647669 50
1776647674 50
1776647679 50
1776647684 50
1776647689 50
1776647694 55
1776647699 55
1776647704 55
1776647709 60
1776647714 60
1776647719 60
```
</details>

---

