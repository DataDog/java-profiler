---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 10:47:24 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 10 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (3 unique values: 29-50 cores)</summary>

```
1791383971 29
1791383976 29
1791383981 29
1791383986 50
1791383991 50
1791383996 50
1791384001 50
1791384006 48
1791384011 48
1791384016 48
1791384021 48
1791384026 48
1791384031 48
1791384036 48
1791384041 48
1791384046 48
1791384051 48
1791384056 48
1791384061 48
1791384066 48
```
</details>

---

