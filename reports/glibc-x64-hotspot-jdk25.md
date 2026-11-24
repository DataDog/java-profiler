---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:39:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 53-57 cores)</summary>

```
1795537859 57
1795537864 57
1795537869 57
1795537874 57
1795537879 57
1795537884 57
1795537889 57
1795537894 57
1795537899 57
1795537904 57
1795537909 55
1795537914 55
1795537919 55
1795537924 55
1795537929 55
1795537934 55
1795537939 55
1795537944 55
1795537949 55
1795537954 55
```
</details>

---

