---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-20 10:05:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 65-81 cores)</summary>

```
1776693501 76
1776693506 76
1776693511 76
1776693516 81
1776693521 81
1776693526 76
1776693531 76
1776693536 76
1776693541 76
1776693546 76
1776693551 71
1776693556 71
1776693561 71
1776693566 72
1776693571 72
1776693576 70
1776693581 70
1776693586 68
1776693591 68
1776693596 68
```
</details>

---

