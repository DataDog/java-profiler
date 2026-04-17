---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-17 11:46:56 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 48-58 cores)</summary>

```
1776440572 51
1776440577 48
1776440582 48
1776440587 48
1776440592 48
1776440597 52
1776440602 52
1776440607 58
1776440612 58
1776440617 58
1776440622 58
1776440627 58
1776440632 58
1776440637 58
1776440642 58
1776440647 58
1776440652 58
1776440657 58
1776440662 58
1776440667 58
```
</details>

---

