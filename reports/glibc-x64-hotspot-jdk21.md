---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:54:33 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 67-71 cores)</summary>

```
1791470919 69
1791470924 71
1791470929 71
1791470934 71
1791470939 71
1791470944 71
1791470949 71
1791470954 69
1791470959 69
1791470964 69
1791470969 67
1791470974 67
1791470979 67
1791470984 67
1791470989 69
1791470994 69
1791470999 69
1791471004 69
1791471009 69
1791471014 69
```
</details>

---

