---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-30 09:25:04 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777555318 64
1777555323 64
1777555328 64
1777555333 64
1777555338 64
1777555343 64
1777555348 64
1777555353 64
1777555358 64
1777555363 64
1777555368 64
1777555373 64
1777555378 64
1777555383 64
1777555388 64
1777555393 64
1777555398 64
1777555403 64
1777555408 64
1777555413 64
```
</details>

---

