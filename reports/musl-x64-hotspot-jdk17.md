---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 11:14:28 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1776265593 14
1776265598 14
1776265604 14
1776265609 14
1776265614 14
1776265619 14
1776265624 14
1776265629 14
1776265634 14
1776265639 14
1776265644 9
1776265649 9
1776265654 9
1776265659 9
1776265664 9
1776265669 9
1776265674 9
1776265679 9
1776265684 9
1776265689 9
```
</details>

---

