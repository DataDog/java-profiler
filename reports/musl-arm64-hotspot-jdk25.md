---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:14:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795529343 33
1795529348 33
1795529353 33
1795529358 33
1795529363 33
1795529368 64
1795529373 64
1795529378 64
1795529383 64
1795529388 64
1795529393 64
1795529398 64
1795529403 64
1795529408 64
1795529413 64
1795529418 64
1795529423 64
1795529428 64
1795529433 64
1795529438 64
```
</details>

---

