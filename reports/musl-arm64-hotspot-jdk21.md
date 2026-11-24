---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:14:33 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 13 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1795529333 43
1795529338 43
1795529343 43
1795529348 43
1795529353 43
1795529358 43
1795529363 43
1795529368 43
1795529373 43
1795529378 43
1795529383 43
1795529388 43
1795529393 43
1795529398 43
1795529404 43
1795529409 43
1795529414 43
1795529419 43
1795529424 43
1795529429 38
```
</details>

---

