---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:54:33 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1791470924 74
1791470929 74
1791470934 72
1791470939 72
1791470944 72
1791470949 72
1791470954 72
1791470959 72
1791470964 74
1791470969 74
1791470974 74
1791470979 74
1791470984 74
1791470989 74
1791470994 74
1791470999 74
1791471004 74
1791471009 74
1791471014 74
1791471019 74
```
</details>

---

