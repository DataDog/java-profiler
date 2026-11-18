---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:31:17 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 12 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 59-68 cores)</summary>

```
1795008278 59
1795008283 59
1795008288 59
1795008293 59
1795008298 59
1795008303 59
1795008308 59
1795008313 59
1795008318 59
1795008323 59
1795008328 59
1795008333 59
1795008338 59
1795008343 59
1795008348 59
1795008353 59
1795008358 59
1795008363 68
1795008368 68
1795008373 68
```
</details>

---

