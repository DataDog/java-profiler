---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 08:19:29 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 517 |

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
1795698966 79
1795698971 77
1795698976 77
1795698981 77
1795698986 77
1795698991 77
```
</details>

---

