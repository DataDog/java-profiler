---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:47:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 986 |
| Sample Rate | 16.43/sec |
| Health Score | 1027% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 40-44 cores)</summary>

```
1794310974 44
1794310979 44
1794310984 44
1794310989 44
1794310994 44
1794310999 44
1794311004 44
1794311009 44
1794311014 44
1794311019 44
1794311024 40
1794311029 40
1794311034 40
1794311039 40
1794311044 40
1794311049 40
1794311054 40
1794311059 40
1794311064 40
1794311069 40
```
</details>

---

