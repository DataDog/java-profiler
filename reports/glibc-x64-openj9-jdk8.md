---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-23 04:28:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 74-90 cores)</summary>

```
1776932482 74
1776932487 74
1776932492 85
1776932497 85
1776932502 85
1776932507 85
1776932512 85
1776932517 85
1776932522 85
1776932527 85
1776932532 85
1776932537 85
1776932542 85
1776932547 85
1776932552 85
1776932557 85
1776932562 85
1776932567 85
1776932572 90
1776932577 90
```
</details>

---

