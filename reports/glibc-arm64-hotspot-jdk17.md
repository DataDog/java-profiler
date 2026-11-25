---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 08:34:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795613386 47
1795613391 47
1795613396 47
1795613401 47
1795613406 47
1795613411 64
1795613416 64
1795613421 64
1795613426 64
1795613431 64
1795613436 64
1795613441 64
1795613446 64
1795613451 64
1795613456 64
1795613461 64
1795613466 64
1795613471 64
1795613476 64
1795613481 64
```
</details>

---

