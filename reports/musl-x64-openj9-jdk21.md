---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 06:24:37 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 8 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 10-21 cores)</summary>

```
1793704761 10
1793704766 10
1793704771 10
1793704776 21
1793704781 21
1793704786 21
1793704791 21
1793704796 21
1793704801 21
1793704806 21
1793704811 21
1793704816 21
1793704821 21
1793704826 21
1793704831 21
1793704836 21
1793704841 21
1793704846 21
1793704851 21
1793704856 21
```
</details>

---

