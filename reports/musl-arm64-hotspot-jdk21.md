---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 16:40:45 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 14 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (3 unique values: 34-51 cores)</summary>

```
1794346466 34
1794346471 34
1794346476 34
1794346481 34
1794346486 34
1794346491 39
1794346496 39
1794346501 39
1794346506 39
1794346511 39
1794346516 39
1794346521 39
1794346526 39
1794346531 39
1794346536 39
1794346541 39
1794346546 39
1794346551 39
1794346556 39
1794346561 39
```
</details>

---

