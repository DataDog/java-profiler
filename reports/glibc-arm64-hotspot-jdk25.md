---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-26 10:30:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 56-63 cores)</summary>

```
1787754319 63
1787754324 63
1787754329 59
1787754334 59
1787754339 59
1787754344 59
1787754349 59
1787754354 59
1787754359 56
1787754364 56
1787754369 56
1787754374 56
1787754379 56
1787754384 56
1787754389 56
1787754394 56
1787754399 56
1787754404 56
1787754409 56
1787754414 56
```
</details>

---

