---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-20 10:05:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 78-84 cores)</summary>

```
1776693486 82
1776693491 82
1776693496 82
1776693501 78
1776693506 78
1776693511 78
1776693516 78
1776693521 82
1776693526 82
1776693531 82
1776693536 82
1776693541 82
1776693546 82
1776693551 82
1776693556 80
1776693561 80
1776693566 80
1776693571 84
1776693576 84
1776693581 84
```
</details>

---

