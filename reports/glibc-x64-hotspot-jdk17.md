---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 16:14:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 8 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 9-32 cores)</summary>

```
1786133317 9
1786133322 9
1786133327 30
1786133332 30
1786133337 30
1786133342 30
1786133347 30
1786133352 30
1786133357 32
1786133362 32
1786133367 32
1786133372 32
1786133377 32
1786133382 32
1786133387 32
1786133392 32
1786133397 32
1786133402 32
1786133407 32
1786133412 32
```
</details>

---

