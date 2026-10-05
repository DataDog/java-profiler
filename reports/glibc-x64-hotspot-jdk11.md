---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 00:55:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 29-46 cores)</summary>

```
1791175859 31
1791175864 31
1791175869 31
1791175874 31
1791175879 31
1791175884 31
1791175889 31
1791175894 29
1791175899 29
1791175904 29
1791175909 29
1791175914 29
1791175919 29
1791175924 29
1791175929 29
1791175934 29
1791175939 29
1791175944 29
1791175949 29
1791175954 29
```
</details>

---

