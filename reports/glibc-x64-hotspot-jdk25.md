---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-28 18:13:24 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1777413976 32
1777413981 32
1777413986 32
1777413991 32
1777413996 32
1777414001 27
1777414006 27
1777414011 27
1777414016 27
1777414021 27
1777414026 27
1777414031 27
1777414036 27
1777414041 25
1777414046 25
1777414051 25
1777414056 25
1777414061 25
1777414066 25
1777414071 25
```
</details>

---

