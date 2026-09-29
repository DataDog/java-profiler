---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-29 06:43:04 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 36-44 cores)</summary>

```
1790678322 36
1790678327 36
1790678332 36
1790678337 36
1790678342 36
1790678347 36
1790678352 36
1790678357 36
1790678362 44
1790678367 44
1790678372 44
1790678377 44
1790678382 44
1790678387 44
1790678392 44
1790678397 44
1790678402 44
1790678407 44
1790678412 44
1790678417 44
```
</details>

---

