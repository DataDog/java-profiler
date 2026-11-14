---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-14 05:55:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 61-81 cores)</summary>

```
1794653429 81
1794653434 81
1794653439 81
1794653444 81
1794653449 81
1794653454 81
1794653459 81
1794653464 81
1794653469 81
1794653474 81
1794653479 81
1794653484 81
1794653489 81
1794653494 81
1794653499 81
1794653504 61
1794653509 61
1794653514 61
1794653519 61
1794653524 61
```
</details>

---

