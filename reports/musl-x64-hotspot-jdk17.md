---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:21:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1794507344 20
1794507349 20
1794507354 20
1794507359 20
1794507364 22
1794507369 22
1794507374 22
1794507379 22
1794507384 22
1794507389 22
1794507394 22
1794507399 22
1794507404 22
1794507409 22
1794507414 22
1794507419 22
1794507424 22
1794507429 22
1794507434 22
1794507439 22
```
</details>

---

