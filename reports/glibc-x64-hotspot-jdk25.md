---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 08:19:29 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1795698896 81
1795698901 81
1795698906 81
1795698911 81
1795698916 81
1795698921 81
1795698926 81
1795698931 81
1795698936 81
1795698941 81
1795698946 81
1795698951 81
1795698956 79
1795698961 79
1795698966 77
1795698971 77
1795698976 77
1795698981 77
1795698986 77
1795698991 77
```
</details>

---

