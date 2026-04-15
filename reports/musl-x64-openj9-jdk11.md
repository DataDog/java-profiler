---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 11:36:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 21-28 cores)</summary>

```
1776266673 21
1776266678 23
1776266683 23
1776266688 23
1776266693 23
1776266698 23
1776266703 23
1776266708 23
1776266713 23
1776266718 23
1776266723 23
1776266728 23
1776266733 23
1776266738 23
1776266743 25
1776266748 25
1776266753 25
1776266758 25
1776266763 28
1776266768 28
```
</details>

---

