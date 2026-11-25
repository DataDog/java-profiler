---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:29:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1795627433 72
1795627438 72
1795627443 72
1795627448 72
1795627453 72
1795627458 72
1795627463 72
1795627468 72
1795627473 74
1795627478 74
1795627483 74
1795627488 74
1795627493 74
1795627498 74
1795627503 74
1795627508 74
1795627513 74
1795627518 74
1795627523 74
1795627528 74
```
</details>

---

