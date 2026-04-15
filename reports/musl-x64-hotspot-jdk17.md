---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 08:57:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 9 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 16-51 cores)</summary>

```
1776257547 21
1776257552 21
1776257557 25
1776257562 25
1776257567 25
1776257572 25
1776257577 25
1776257582 25
1776257587 25
1776257592 25
1776257597 16
1776257602 16
1776257607 16
1776257612 16
1776257617 16
1776257622 16
1776257627 51
1776257632 51
1776257637 31
1776257642 31
```
</details>

---

