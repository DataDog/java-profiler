---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 11:08:48 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 14 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794931428 64
1794931433 64
1794931438 64
1794931443 64
1794931448 64
1794931453 64
1794931458 64
1794931463 64
1794931468 64
1794931473 64
1794931478 64
1794931483 64
1794931488 64
1794931493 64
1794931498 64
1794931503 64
1794931508 64
1794931513 64
1794931518 64
1794931523 64
```
</details>

---

