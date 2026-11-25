---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:28:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1795627394 78
1795627399 78
1795627404 78
1795627409 78
1795627414 76
1795627419 76
1795627424 76
1795627429 76
1795627434 76
1795627439 76
1795627444 76
1795627449 76
1795627454 76
1795627459 76
1795627464 76
1795627469 76
1795627474 76
1795627479 76
1795627484 76
1795627489 76
```
</details>

---

