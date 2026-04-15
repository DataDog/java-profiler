---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 11:14:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776265578 59
1776265583 59
1776265588 59
1776265593 59
1776265598 59
1776265603 59
1776265608 59
1776265613 59
1776265618 59
1776265623 59
1776265628 59
1776265633 59
1776265638 59
1776265643 59
1776265648 59
1776265653 59
1776265658 64
1776265663 64
1776265668 64
1776265673 64
```
</details>

---

