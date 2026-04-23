---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 15:21:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 13 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1776971720 22
1776971725 22
1776971730 27
1776971735 27
1776971740 27
1776971745 27
1776971750 27
1776971755 27
1776971760 27
1776971765 27
1776971770 27
1776971775 27
1776971780 27
1776971785 27
1776971790 27
1776971795 27
1776971800 27
1776971805 27
1776971810 27
1776971815 22
```
</details>

---

