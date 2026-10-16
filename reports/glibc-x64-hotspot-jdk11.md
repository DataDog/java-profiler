---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 05:16:14 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 889 |
| Sample Rate | 14.82/sec |
| Health Score | 926% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 12-30 cores)</summary>

```
1792141905 12
1792141910 12
1792141916 12
1792141921 12
1792141926 30
1792141931 30
1792141936 30
1792141941 30
1792141946 30
1792141951 30
1792141956 30
1792141961 30
1792141966 30
1792141971 30
1792141976 30
1792141981 30
1792141986 30
1792141991 30
1792141996 30
1792142001 30
```
</details>

---

