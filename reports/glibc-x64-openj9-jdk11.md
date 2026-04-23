---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 14:32:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 900 |
| Sample Rate | 15.00/sec |
| Health Score | 938% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1776968734 39
1776968739 39
1776968744 39
1776968749 35
1776968754 35
1776968759 35
1776968764 35
1776968769 35
1776968774 35
1776968779 35
1776968784 35
1776968789 35
1776968794 35
1776968800 35
1776968805 35
1776968810 40
1776968815 40
1776968820 40
1776968825 40
1776968830 40
```
</details>

---

