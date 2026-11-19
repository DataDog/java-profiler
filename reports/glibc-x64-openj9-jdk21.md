---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:16:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 10 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (5 unique values: 61-74 cores)</summary>

```
1795108364 63
1795108369 63
1795108374 63
1795108379 63
1795108384 63
1795108389 63
1795108394 63
1795108399 63
1795108404 63
1795108409 61
1795108414 61
1795108419 70
1795108424 70
1795108429 70
1795108434 70
1795108439 70
1795108444 70
1795108449 70
1795108454 70
1795108459 70
```
</details>

---

