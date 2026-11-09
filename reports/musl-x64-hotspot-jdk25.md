---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 18:56:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 20-72 cores)</summary>

```
1794268261 20
1794268266 20
1794268271 20
1794268276 20
1794268281 20
1794268286 20
1794268291 20
1794268296 20
1794268301 53
1794268306 53
1794268311 72
1794268316 72
1794268321 23
1794268326 23
1794268331 23
1794268336 23
1794268341 21
1794268346 21
1794268351 21
1794268356 21
```
</details>

---

