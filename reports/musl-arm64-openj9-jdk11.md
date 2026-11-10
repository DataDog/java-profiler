---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:47:21 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1794310969 48
1794310974 48
1794310979 44
1794310984 44
1794310989 44
1794310994 44
1794310999 44
1794311004 44
1794311009 44
1794311014 44
1794311019 44
1794311024 44
1794311029 40
1794311034 40
1794311039 40
1794311044 40
1794311049 40
1794311055 40
1794311060 40
1794311065 40
```
</details>

---

