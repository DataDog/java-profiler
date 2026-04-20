---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 10:05:08 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 61-78 cores)</summary>

```
1776693468 74
1776693473 74
1776693478 74
1776693484 74
1776693489 74
1776693494 74
1776693499 74
1776693504 78
1776693509 78
1776693514 78
1776693519 78
1776693524 78
1776693529 78
1776693534 78
1776693539 78
1776693544 78
1776693549 78
1776693554 66
1776693559 66
1776693564 66
```
</details>

---

