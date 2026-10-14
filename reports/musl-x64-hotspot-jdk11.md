---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 10:47:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (5 unique values: 75-85 cores)</summary>

```
1791988869 76
1791988874 75
1791988879 75
1791988884 75
1791988889 75
1791988894 75
1791988899 75
1791988904 75
1791988909 75
1791988914 75
1791988919 77
1791988924 77
1791988929 77
1791988934 77
1791988939 77
1791988944 77
1791988949 75
1791988954 75
1791988959 75
1791988964 75
```
</details>

---

