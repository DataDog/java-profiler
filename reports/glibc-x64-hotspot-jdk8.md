---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-15 11:14:26 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776265598 59
1776265603 59
1776265608 59
1776265613 59
1776265618 59
1776265623 59
1776265628 59
1776265633 59
1776265638 59
1776265643 64
1776265648 64
1776265653 64
1776265658 64
1776265663 64
1776265668 64
1776265673 64
1776265678 64
1776265683 64
1776265688 64
1776265693 64
```
</details>

---

