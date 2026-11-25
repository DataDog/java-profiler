---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:28:00 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 37 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 38 |
| Sample Rate | 0.63/sec |
| Health Score | 39% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795627383 64
1795627388 64
1795627393 64
1795627398 64
1795627403 64
1795627408 64
1795627413 64
1795627418 64
1795627423 64
1795627428 64
1795627433 64
1795627438 64
1795627443 64
1795627448 64
1795627453 64
1795627458 64
1795627463 64
1795627468 64
1795627473 64
1795627478 64
```
</details>

---

