---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-27 09:40:17 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787837715 66
1787837720 64
1787837725 64
1787837730 64
1787837735 64
1787837740 64
1787837745 64
1787837750 64
1787837755 64
1787837760 64
1787837765 64
1787837770 64
1787837775 64
1787837780 66
1787837785 66
1787837790 66
1787837795 66
1787837800 66
1787837805 66
1787837810 66
```
</details>

---

