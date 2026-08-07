---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 10:30:56 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 73-96 cores)</summary>

```
1786112791 91
1786112796 91
1786112801 91
1786112806 91
1786112811 96
1786112816 96
1786112821 96
1786112826 96
1786112831 96
1786112836 96
1786112841 96
1786112846 96
1786112851 96
1786112856 96
1786112861 96
1786112866 96
1786112871 75
1786112876 75
1786112881 73
1786112886 73
```
</details>

---

