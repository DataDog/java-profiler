---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 07:26:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (5 unique values: 60-78 cores)</summary>

```
1795177338 60
1795177343 60
1795177348 60
1795177353 60
1795177358 60
1795177363 60
1795177368 60
1795177373 60
1795177378 66
1795177383 66
1795177388 66
1795177393 66
1795177398 63
1795177403 63
1795177408 63
1795177413 74
1795177418 74
1795177423 74
1795177428 74
1795177433 74
```
</details>

---

