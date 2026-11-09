---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 12:24:37 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (4 unique values: 69-77 cores)</summary>

```
1794244740 77
1794244745 77
1794244750 77
1794244755 77
1794244760 77
1794244765 77
1794244770 74
1794244775 74
1794244780 74
1794244785 74
1794244790 69
1794244795 69
1794244800 69
1794244805 69
1794244810 74
1794244815 74
1794244820 74
1794244825 72
1794244830 72
1794244835 72
```
</details>

---

