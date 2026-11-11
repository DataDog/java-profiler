---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 05:55:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 10 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (5 unique values: 40-48 cores)</summary>

```
1794394288 45
1794394293 45
1794394298 40
1794394303 40
1794394308 42
1794394313 42
1794394318 42
1794394323 43
1794394328 43
1794394333 43
1794394338 43
1794394343 43
1794394348 43
1794394353 43
1794394358 43
1794394363 48
1794394368 48
1794394373 48
1794394378 48
1794394383 48
```
</details>

---

