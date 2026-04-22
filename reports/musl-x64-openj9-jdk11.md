---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 14:02:54 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1036 |
| Sample Rate | 17.27/sec |
| Health Score | 1079% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 49-61 cores)</summary>

```
1776880793 51
1776880798 51
1776880803 51
1776880808 51
1776880813 51
1776880818 49
1776880823 49
1776880828 49
1776880833 49
1776880838 59
1776880843 59
1776880848 59
1776880853 59
1776880858 61
1776880863 61
1776880868 61
1776880873 61
1776880878 61
1776880883 61
1776880888 61
```
</details>

---

