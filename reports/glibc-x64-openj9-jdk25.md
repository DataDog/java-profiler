---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 16:53:36 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 51-70 cores)</summary>

```
1794433748 63
1794433753 63
1794433758 63
1794433763 63
1794433768 63
1794433773 63
1794433778 68
1794433783 68
1794433788 68
1794433793 51
1794433798 51
1794433803 51
1794433808 51
1794433813 70
1794433818 70
1794433823 70
1794433828 70
1794433833 70
1794433838 70
1794433843 70
```
</details>

---

