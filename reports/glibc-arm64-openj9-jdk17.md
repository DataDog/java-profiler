---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 05:04:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 12 |
| Allocations | 103 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793178006 48
1793178011 48
1793178016 48
1793178021 48
1793178026 48
1793178031 48
1793178036 43
1793178041 43
1793178046 43
1793178051 43
1793178056 43
1793178061 43
1793178066 43
1793178071 43
1793178076 43
1793178081 43
1793178086 43
1793178091 43
1793178096 43
1793178101 43
```
</details>

---

