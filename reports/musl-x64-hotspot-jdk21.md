---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:05:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 988 |
| Sample Rate | 16.47/sec |
| Health Score | 1029% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 87-92 cores)</summary>

```
1776693467 91
1776693472 91
1776693477 91
1776693482 91
1776693487 91
1776693492 91
1776693497 91
1776693502 91
1776693507 91
1776693512 91
1776693517 87
1776693522 87
1776693527 87
1776693532 87
1776693537 87
1776693542 87
1776693547 87
1776693552 87
1776693557 87
1776693562 87
```
</details>

---

