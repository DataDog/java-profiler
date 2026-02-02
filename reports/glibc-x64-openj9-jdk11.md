---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-02 12:03:38 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 26-32 cores)</summary>

```
1770051374 32
1770051379 32
1770051384 32
1770051389 32
1770051394 32
1770051399 32
1770051404 32
1770051409 32
1770051414 26
1770051419 26
1770051424 26
1770051429 26
1770051434 26
1770051439 26
1770051444 26
1770051449 26
1770051454 26
1770051459 26
1770051464 26
1770051469 26
```
</details>

---

