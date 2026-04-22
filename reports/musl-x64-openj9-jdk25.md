---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 14:04:02 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 12 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 52-61 cores)</summary>

```
1776880716 59
1776880721 59
1776880726 59
1776880731 59
1776880736 59
1776880741 59
1776880746 59
1776880751 59
1776880756 59
1776880761 59
1776880766 59
1776880771 59
1776880776 59
1776880781 61
1776880786 61
1776880791 61
1776880796 61
1776880801 61
1776880806 52
1776880811 52
```
</details>

---

