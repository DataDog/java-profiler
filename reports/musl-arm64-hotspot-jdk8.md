---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-11 04:54:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1794390404 54
1794390409 59
1794390414 59
1794390419 59
1794390424 59
1794390429 59
1794390434 59
1794390439 59
1794390444 59
1794390449 59
1794390454 59
1794390459 59
1794390464 59
1794390469 59
1794390475 59
1794390480 59
1794390485 59
1794390490 59
1794390495 59
1794390500 59
```
</details>

---

