---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:25:29 EST

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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795706333 64
1795706338 64
1795706343 64
1795706348 64
1795706353 64
1795706358 64
1795706363 64
1795706368 64
1795706373 64
1795706378 64
1795706383 64
1795706388 64
1795706393 64
1795706398 64
1795706403 64
1795706408 64
1795706413 64
1795706418 64
1795706423 64
1795706428 64
```
</details>

---

