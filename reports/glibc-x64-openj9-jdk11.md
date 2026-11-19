---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:48:43 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1795095813 53
1795095818 53
1795095823 53
1795095828 53
1795095833 53
1795095838 53
1795095843 53
1795095848 53
1795095853 53
1795095858 53
1795095863 53
1795095868 53
1795095873 53
1795095878 53
1795095883 53
1795095888 51
1795095893 51
1795095898 51
1795095903 51
1795095908 51
```
</details>

---

