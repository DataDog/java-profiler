---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 02:47:22 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 68-71 cores)</summary>

```
1795074247 71
1795074252 71
1795074257 68
1795074262 68
1795074267 68
1795074272 68
1795074277 70
1795074282 70
1795074287 68
1795074292 68
1795074297 68
1795074302 68
1795074307 68
1795074312 68
1795074317 68
1795074322 68
1795074327 70
1795074332 70
1795074337 70
1795074342 70
```
</details>

---

