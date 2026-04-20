---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 10:05:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 43-63 cores)</summary>

```
1776693538 47
1776693543 47
1776693548 47
1776693553 47
1776693558 47
1776693563 43
1776693568 43
1776693573 43
1776693578 43
1776693583 47
1776693588 47
1776693594 47
1776693599 47
1776693604 47
1776693609 47
1776693614 47
1776693619 47
1776693624 47
1776693629 47
1776693634 47
```
</details>

---

