---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:53:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (7 unique values: 66-82 cores)</summary>

```
1794433736 72
1794433741 72
1794433746 72
1794433751 70
1794433756 70
1794433761 70
1794433766 70
1794433771 70
1794433776 72
1794433781 72
1794433786 72
1794433791 70
1794433796 70
1794433801 80
1794433806 80
1794433811 82
1794433816 82
1794433821 82
1794433826 66
1794433831 66
```
</details>

---

