---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 08:34:18 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795613376 94
1795613381 94
1795613386 94
1795613391 94
1795613396 94
1795613401 94
1795613406 94
1795613411 94
1795613416 94
1795613421 94
1795613426 94
1795613431 94
1795613436 94
1795613441 94
1795613446 94
1795613451 94
1795613456 94
1795613461 94
1795613466 94
1795613471 96
```
</details>

---

