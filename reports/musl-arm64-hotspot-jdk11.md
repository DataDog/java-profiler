---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 03:00:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (4 unique values: 27-48 cores)</summary>

```
1794988414 28
1794988419 28
1794988424 28
1794988429 28
1794988434 28
1794988439 28
1794988444 28
1794988449 28
1794988454 28
1794988459 28
1794988464 28
1794988469 28
1794988474 28
1794988479 27
1794988484 27
1794988489 27
1794988494 27
1794988499 27
1794988505 27
1794988510 27
```
</details>

---

