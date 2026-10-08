---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:53:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791470909 43
1791470914 43
1791470919 43
1791470924 43
1791470929 48
1791470934 48
1791470939 48
1791470944 48
1791470949 48
1791470954 48
1791470959 48
1791470964 48
1791470969 48
1791470974 48
1791470979 48
1791470984 48
1791470989 48
1791470994 48
1791470999 48
1791471004 48
```
</details>

---

