---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:17:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 935 |
| Sample Rate | 15.58/sec |
| Health Score | 974% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 27-53 cores)</summary>

```
1794406314 27
1794406319 27
1794406324 27
1794406330 27
1794406335 27
1794406340 27
1794406345 27
1794406350 27
1794406355 27
1794406360 27
1794406365 27
1794406370 27
1794406375 27
1794406380 27
1794406385 33
1794406390 33
1794406395 33
1794406400 53
1794406405 53
1794406410 53
```
</details>

---

