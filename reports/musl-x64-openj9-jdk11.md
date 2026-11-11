---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:17:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 70-92 cores)</summary>

```
1794406314 72
1794406319 72
1794406324 72
1794406329 70
1794406334 70
1794406339 70
1794406344 70
1794406349 92
1794406354 92
1794406359 92
1794406364 92
1794406369 92
1794406374 92
1794406379 92
1794406384 92
1794406389 92
1794406394 92
1794406399 92
1794406404 92
1794406409 92
```
</details>

---

