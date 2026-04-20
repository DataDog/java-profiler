---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-19 21:19:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (6 unique values: 74-93 cores)</summary>

```
1776647619 74
1776647624 74
1776647629 74
1776647634 76
1776647639 76
1776647644 76
1776647649 76
1776647654 76
1776647659 76
1776647664 76
1776647669 76
1776647674 76
1776647679 81
1776647684 81
1776647689 81
1776647694 81
1776647699 81
1776647704 86
1776647709 86
1776647714 91
```
</details>

---

