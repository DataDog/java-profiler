---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:49:58 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 68-76 cores)</summary>

```
1789731902 72
1789731907 74
1789731912 74
1789731917 74
1789731922 76
1789731927 76
1789731932 76
1789731937 76
1789731942 76
1789731947 76
1789731952 76
1789731958 76
1789731963 76
1789731968 76
1789731973 76
1789731978 76
1789731983 76
1789731988 76
1789731993 68
1789731998 68
```
</details>

---

