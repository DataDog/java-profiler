---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:14:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795529308 28
1795529313 28
1795529318 28
1795529323 28
1795529328 28
1795529333 28
1795529338 33
1795529343 33
1795529348 33
1795529353 33
1795529358 33
1795529363 33
1795529368 33
1795529373 33
1795529378 33
1795529383 33
1795529388 33
1795529393 33
1795529398 33
1795529403 33
```
</details>

---

