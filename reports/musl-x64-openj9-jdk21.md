---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:05:08 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 21-26 cores)</summary>

```
1776693469 21
1776693474 21
1776693479 21
1776693484 21
1776693489 21
1776693494 21
1776693499 21
1776693504 21
1776693509 21
1776693514 21
1776693519 21
1776693524 21
1776693529 21
1776693534 21
1776693539 24
1776693544 24
1776693549 24
1776693554 24
1776693559 26
1776693564 26
```
</details>

---

