---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 18:56:12 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 23-32 cores)</summary>

```
1794268276 30
1794268281 30
1794268286 30
1794268291 32
1794268296 32
1794268301 32
1794268306 32
1794268311 32
1794268316 32
1794268321 32
1794268326 32
1794268331 32
1794268336 32
1794268341 32
1794268346 32
1794268351 32
1794268356 32
1794268361 32
1794268366 32
1794268371 32
```
</details>

---

