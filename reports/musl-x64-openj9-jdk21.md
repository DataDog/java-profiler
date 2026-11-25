---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:34:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 875 |
| Sample Rate | 14.58/sec |
| Health Score | 911% |
| Threads | 10 |
| Allocations | 482 |

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

