---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 14:02:54 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 18-28 cores)</summary>

```
1776880746 26
1776880751 26
1776880756 26
1776880761 26
1776880766 26
1776880771 28
1776880776 28
1776880781 28
1776880786 28
1776880791 28
1776880796 28
1776880801 19
1776880806 19
1776880811 18
1776880816 18
1776880821 18
1776880826 18
1776880831 18
1776880836 18
1776880841 18
```
</details>

---

