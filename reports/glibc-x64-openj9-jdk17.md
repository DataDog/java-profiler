---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 08:33:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (4 unique values: 50-64 cores)</summary>

```
1791980924 50
1791980929 59
1791980934 59
1791980939 64
1791980944 64
1791980949 64
1791980954 64
1791980959 64
1791980964 62
1791980969 62
1791980974 62
1791980979 62
1791980984 62
1791980989 62
1791980994 62
1791980999 62
1791981004 62
1791981009 62
1791981014 62
1791981019 62
```
</details>

---

