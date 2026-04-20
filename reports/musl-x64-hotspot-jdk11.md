---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 05:36:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 64-81 cores)</summary>

```
1776677498 64
1776677503 64
1776677508 64
1776677513 69
1776677519 69
1776677524 69
1776677529 69
1776677534 69
1776677539 69
1776677544 81
1776677549 81
1776677554 81
1776677559 81
1776677564 81
1776677569 81
1776677574 81
1776677579 81
1776677584 81
1776677589 81
1776677594 81
```
</details>

---

