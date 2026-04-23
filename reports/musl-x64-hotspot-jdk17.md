---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-23 14:32:13 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 70-81 cores)</summary>

```
1776968715 81
1776968720 79
1776968725 79
1776968730 79
1776968735 79
1776968740 79
1776968745 79
1776968750 79
1776968755 79
1776968760 79
1776968765 79
1776968770 79
1776968775 79
1776968780 79
1776968785 79
1776968790 79
1776968795 79
1776968800 70
1776968805 70
1776968810 70
```
</details>

---

