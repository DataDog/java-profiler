---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:31:29 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 965 |
| Sample Rate | 16.08/sec |
| Health Score | 1005% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1795530349 64
1795530354 64
1795530359 64
1795530364 64
1795530369 64
1795530374 64
1795530379 66
1795530384 66
1795530389 66
1795530394 64
1795530399 64
1795530404 64
1795530409 64
1795530414 64
1795530419 66
1795530424 66
1795530429 66
1795530434 66
1795530439 66
1795530444 66
```
</details>

---

