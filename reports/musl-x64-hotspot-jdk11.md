---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:43:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 937 |
| Sample Rate | 15.62/sec |
| Health Score | 976% |
| Threads | 11 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (4 unique values: 46-77 cores)</summary>

```
1778150329 72
1778150334 77
1778150339 77
1778150344 77
1778150349 50
1778150354 50
1778150359 50
1778150364 50
1778150369 50
1778150374 50
1778150379 50
1778150384 50
1778150389 50
1778150394 50
1778150399 50
1778150404 50
1778150409 50
1778150414 50
1778150419 50
1778150424 50
```
</details>

---

