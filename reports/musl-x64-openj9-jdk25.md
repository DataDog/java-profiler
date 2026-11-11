---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 13:18:19 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 437 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 63-68 cores)</summary>

```
1794420788 68
1794420793 68
1794420798 68
1794420803 68
1794420808 68
1794420813 68
1794420818 68
1794420823 68
1794420828 68
1794420833 68
1794420838 68
1794420843 68
1794420848 68
1794420853 68
1794420858 68
1794420864 68
1794420869 68
1794420874 68
1794420879 68
1794420884 68
```
</details>

---

