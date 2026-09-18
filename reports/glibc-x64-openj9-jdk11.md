---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:48:04 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1103 |
| Sample Rate | 18.38/sec |
| Health Score | 1149% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 70-76 cores)</summary>

```
1789731829 72
1789731834 72
1789731839 72
1789731844 72
1789731849 72
1789731854 72
1789731859 72
1789731864 70
1789731869 70
1789731874 70
1789731879 72
1789731884 72
1789731889 72
1789731894 72
1789731899 72
1789731904 72
1789731909 74
1789731914 74
1789731919 74
1789731924 76
```
</details>

---

