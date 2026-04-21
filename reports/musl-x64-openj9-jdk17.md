---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-21 07:29:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1127 |
| Sample Rate | 18.78/sec |
| Health Score | 1174% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 32-44 cores)</summary>

```
1776770457 32
1776770462 32
1776770467 32
1776770472 32
1776770477 32
1776770482 32
1776770487 32
1776770492 32
1776770497 32
1776770502 32
1776770507 32
1776770512 32
1776770517 32
1776770522 32
1776770527 32
1776770532 34
1776770537 34
1776770542 34
1776770547 34
1776770552 34
```
</details>

---

