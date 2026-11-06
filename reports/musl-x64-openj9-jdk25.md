---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 14:19:18 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1793992405 61
1793992410 61
1793992415 61
1793992420 61
1793992425 61
1793992430 61
1793992435 61
1793992440 61
1793992445 61
1793992450 61
1793992455 61
1793992460 61
1793992465 61
1793992470 61
1793992475 59
1793992480 59
1793992485 59
1793992490 59
1793992495 59
1793992500 59
```
</details>

---

