---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:09:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 87-91 cores)</summary>

```
1794495889 88
1794495894 88
1794495899 91
1794495904 91
1794495909 91
1794495914 91
1794495919 91
1794495924 89
1794495929 89
1794495934 89
1794495939 89
1794495944 89
1794495949 89
1794495954 89
1794495959 87
1794495964 87
1794495969 87
1794495974 87
1794495979 87
1794495984 87
```
</details>

---

