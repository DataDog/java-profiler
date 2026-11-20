---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 07:26:37 EST

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 10 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 11-18 cores)</summary>

```
1795177341 18
1795177346 18
1795177351 18
1795177356 18
1795177361 18
1795177366 18
1795177371 18
1795177376 18
1795177381 18
1795177386 18
1795177391 18
1795177396 13
1795177401 13
1795177406 13
1795177411 13
1795177416 13
1795177421 13
1795177426 11
1795177431 11
1795177436 11
```
</details>

---

