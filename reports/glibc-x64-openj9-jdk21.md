---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-21 10:50:24 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 38-46 cores)</summary>

```
1776782618 44
1776782623 44
1776782628 44
1776782633 44
1776782638 44
1776782643 44
1776782648 44
1776782653 44
1776782658 44
1776782663 44
1776782668 44
1776782673 44
1776782678 46
1776782683 46
1776782688 42
1776782693 42
1776782698 42
1776782703 42
1776782708 38
1776782713 38
```
</details>

---

