---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 04:54:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 34 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794390387 47
1794390392 47
1794390397 47
1794390402 47
1794390407 47
1794390412 47
1794390417 47
1794390422 47
1794390427 47
1794390432 47
1794390437 47
1794390442 48
1794390447 48
1794390452 48
1794390457 48
1794390462 48
1794390468 48
1794390473 48
1794390478 48
1794390483 48
```
</details>

---

