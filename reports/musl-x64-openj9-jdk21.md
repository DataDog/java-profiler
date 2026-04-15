---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-15 14:28:20 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 18-27 cores)</summary>

```
1776277518 20
1776277523 20
1776277528 20
1776277533 20
1776277538 20
1776277543 20
1776277548 18
1776277553 18
1776277558 20
1776277563 20
1776277568 22
1776277573 22
1776277578 27
1776277583 27
1776277588 27
1776277593 27
1776277598 27
1776277603 27
1776277608 27
1776277613 27
```
</details>

---

