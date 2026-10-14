---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 04:49:55 EDT

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
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 992 |
| Sample Rate | 16.53/sec |
| Health Score | 1033% |
| Threads | 10 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1791967401 72
1791967406 72
1791967411 72
1791967416 72
1791967421 72
1791967426 72
1791967431 72
1791967436 72
1791967441 72
1791967446 72
1791967451 72
1791967456 72
1791967461 72
1791967466 74
1791967471 74
1791967476 74
1791967481 74
1791967486 74
1791967491 74
1791967496 74
```
</details>

---

