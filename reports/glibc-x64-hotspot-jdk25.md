---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:56:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (5 unique values: 64-79 cores)</summary>

```
1795186364 64
1795186369 73
1795186374 73
1795186379 73
1795186384 73
1795186389 73
1795186394 73
1795186399 73
1795186404 73
1795186409 73
1795186414 73
1795186419 73
1795186424 73
1795186429 75
1795186434 75
1795186439 75
1795186444 75
1795186449 75
1795186454 77
1795186459 77
```
</details>

---

