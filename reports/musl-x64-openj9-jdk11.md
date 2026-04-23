---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 10:22:09 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1021 |
| Sample Rate | 17.02/sec |
| Health Score | 1064% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (5 unique values: 72-87 cores)</summary>

```
1776953796 87
1776953801 87
1776953806 87
1776953811 87
1776953816 87
1776953821 87
1776953826 87
1776953831 85
1776953836 85
1776953841 85
1776953846 85
1776953851 85
1776953856 85
1776953861 85
1776953866 85
1776953871 85
1776953877 81
1776953882 81
1776953887 81
1776953892 72
```
</details>

---

