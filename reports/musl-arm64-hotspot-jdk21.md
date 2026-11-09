---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-08 20:29:10 EST

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1794187475 12
1794187480 12
1794187485 12
1794187490 10
1794187495 10
1794187500 10
1794187505 10
1794187510 10
1794187515 10
1794187520 10
1794187525 10
1794187530 10
1794187535 10
1794187540 12
1794187545 12
1794187550 12
1794187555 12
1794187560 12
1794187565 12
1794187570 12
```
</details>

---

