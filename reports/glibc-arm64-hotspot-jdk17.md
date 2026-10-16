---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 05:17:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 9 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1792141996 49
1792142001 49
1792142006 49
1792142011 49
1792142016 49
1792142021 49
1792142026 51
1792142031 51
1792142036 51
1792142041 51
1792142046 51
1792142051 51
1792142056 51
1792142061 51
1792142066 51
1792142071 51
1792142076 51
1792142081 51
1792142086 51
1792142091 51
```
</details>

---

