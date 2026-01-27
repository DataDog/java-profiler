---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-27 10:22:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 16.27/sec |
| Health Score | 1017% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 22.60/sec |
| Health Score | 1412% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1769526894 32
1769526899 32
1769526904 32
1769526909 32
1769526914 32
1769526919 32
1769526924 32
1769526929 32
1769526934 32
1769526939 32
1769526944 23
1769526949 23
1769526954 23
1769526959 23
1769526964 23
1769526969 23
1769526974 23
1769526979 23
1769526984 23
1769526989 23
```
</details>

---

