---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 06:43:05 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 18-23 cores)</summary>

```
1790678282 23
1790678287 23
1790678292 23
1790678297 23
1790678302 23
1790678307 23
1790678312 23
1790678317 23
1790678322 23
1790678327 23
1790678332 23
1790678337 23
1790678342 23
1790678347 23
1790678352 23
1790678357 23
1790678362 23
1790678367 23
1790678372 23
1790678377 23
```
</details>

---

