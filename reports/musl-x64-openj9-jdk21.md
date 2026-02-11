---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:22:29 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 10 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 13 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (6 unique values: 55-66 cores)</summary>

```
1770826415 57
1770826420 57
1770826425 55
1770826430 55
1770826435 55
1770826440 55
1770826445 59
1770826450 59
1770826455 59
1770826460 59
1770826465 61
1770826470 61
1770826475 61
1770826480 66
1770826485 66
1770826490 66
1770826495 66
1770826500 66
1770826505 66
1770826510 66
```
</details>

---

