---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:05:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 71-81 cores)</summary>

```
1776693472 76
1776693477 76
1776693482 76
1776693487 71
1776693492 71
1776693497 71
1776693502 71
1776693507 71
1776693512 71
1776693517 71
1776693522 71
1776693527 71
1776693532 71
1776693537 71
1776693542 71
1776693547 71
1776693552 71
1776693557 71
1776693562 71
1776693567 81
```
</details>

---

