---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 08:34:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 61-63 cores)</summary>

```
1795613381 63
1795613386 62
1795613391 62
1795613396 62
1795613401 62
1795613406 62
1795613411 62
1795613416 62
1795613421 62
1795613426 61
1795613431 61
1795613436 61
1795613441 61
1795613446 61
1795613451 61
1795613456 61
1795613461 61
1795613466 61
1795613471 61
1795613476 61
```
</details>

---

