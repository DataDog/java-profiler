---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-21 10:50:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1001 |
| Sample Rate | 16.68/sec |
| Health Score | 1042% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1776782632 90
1776782637 90
1776782642 90
1776782647 90
1776782652 90
1776782657 90
1776782662 90
1776782667 90
1776782673 90
1776782678 90
1776782683 90
1776782688 90
1776782693 90
1776782698 90
1776782703 90
1776782708 92
1776782713 92
1776782718 92
1776782723 92
1776782728 92
```
</details>

---

