---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 05:17:21 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (6 unique values: 60-80 cores)</summary>

```
1792141996 69
1792142001 69
1792142006 69
1792142011 80
1792142016 80
1792142021 62
1792142026 62
1792142031 62
1792142036 62
1792142041 62
1792142046 62
1792142051 60
1792142056 60
1792142061 60
1792142066 60
1792142071 62
1792142076 62
1792142081 62
1792142086 62
1792142091 62
```
</details>

---

