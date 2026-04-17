---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-17 11:46:56 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 54-66 cores)</summary>

```
1776440573 66
1776440578 66
1776440583 66
1776440588 66
1776440593 66
1776440598 66
1776440603 66
1776440608 66
1776440613 66
1776440618 54
1776440623 54
1776440628 59
1776440633 59
1776440638 59
1776440643 59
1776440648 59
1776440653 59
1776440658 59
1776440663 59
1776440668 59
```
</details>

---

