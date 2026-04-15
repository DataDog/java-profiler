---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 15:54:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 29-43 cores)</summary>

```
1776282657 43
1776282662 43
1776282667 43
1776282672 43
1776282677 33
1776282682 33
1776282687 33
1776282692 33
1776282697 33
1776282702 33
1776282707 29
1776282712 29
1776282717 29
1776282722 29
1776282727 29
1776282732 29
1776282737 29
1776282742 29
1776282747 29
1776282752 29
```
</details>

---

