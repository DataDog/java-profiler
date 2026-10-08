---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-10-08 10:54:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1791470899 86
1791470904 86
1791470909 86
1791470914 86
1791470919 86
1791470924 86
1791470929 86
1791470934 86
1791470939 86
1791470944 86
1791470949 86
1791470954 86
1791470959 86
1791470964 86
1791470969 86
1791470974 86
1791470979 86
1791470984 86
1791470989 84
1791470994 84
```
</details>

---

