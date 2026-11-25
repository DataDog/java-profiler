---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:28:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 77-82 cores)</summary>

```
1795627379 77
1795627384 77
1795627389 77
1795627394 77
1795627399 77
1795627404 77
1795627409 80
1795627414 80
1795627419 82
1795627424 82
1795627429 82
1795627434 82
1795627439 82
1795627444 82
1795627449 82
1795627454 82
1795627459 82
1795627464 82
1795627469 82
1795627474 82
```
</details>

---

