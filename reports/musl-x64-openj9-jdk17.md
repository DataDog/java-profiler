---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 14:32:14 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 75-85 cores)</summary>

```
1776968714 85
1776968719 85
1776968724 85
1776968729 85
1776968734 85
1776968739 85
1776968744 85
1776968749 85
1776968754 85
1776968759 85
1776968764 75
1776968769 75
1776968774 75
1776968779 75
1776968784 75
1776968789 75
1776968794 75
1776968799 75
1776968804 75
1776968809 79
```
</details>

---

