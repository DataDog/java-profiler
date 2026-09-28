---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-27 21:22:41 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 28-58 cores)</summary>

```
1790558289 28
1790558294 28
1790558299 28
1790558304 28
1790558309 28
1790558314 28
1790558319 28
1790558324 28
1790558329 28
1790558334 28
1790558339 28
1790558344 58
1790558349 58
1790558354 58
1790558359 58
1790558364 58
1790558369 58
1790558374 58
1790558379 58
1790558384 58
```
</details>

---

