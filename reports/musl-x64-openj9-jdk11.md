---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 14:35:37 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 80-93 cores)</summary>

```
1793125815 80
1793125820 80
1793125825 80
1793125830 80
1793125835 80
1793125840 80
1793125845 80
1793125850 80
1793125855 89
1793125860 89
1793125866 89
1793125871 89
1793125876 89
1793125881 89
1793125886 89
1793125891 89
1793125896 89
1793125901 89
1793125906 89
1793125911 89
```
</details>

---

