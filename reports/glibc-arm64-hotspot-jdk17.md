---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 04:53:58 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 14 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1794390389 54
1794390394 54
1794390399 54
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
1794390474 59
1794390479 59
1794390484 59
```
</details>

---

