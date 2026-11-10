---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 06:47:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 19-21 cores)</summary>

```
1794310973 20
1794310978 20
1794310984 20
1794310989 20
1794310994 20
1794310999 20
1794311004 20
1794311009 20
1794311014 20
1794311019 20
1794311024 21
1794311029 21
1794311034 21
1794311039 19
1794311044 19
1794311049 19
1794311054 19
1794311059 19
1794311064 19
1794311069 19
```
</details>

---

