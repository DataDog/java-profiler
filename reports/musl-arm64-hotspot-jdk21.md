---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 00:57:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1786510435 18
1786510440 18
1786510445 18
1786510450 18
1786510455 18
1786510460 18
1786510465 18
1786510470 16
1786510475 16
1786510480 16
1786510485 16
1786510490 16
1786510495 16
1786510500 16
1786510505 16
1786510510 16
1786510515 16
1786510520 18
1786510525 18
1786510530 18
```
</details>

---

