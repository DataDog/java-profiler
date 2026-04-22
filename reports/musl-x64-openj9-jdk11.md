---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 13:04:06 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1028 |
| Sample Rate | 17.13/sec |
| Health Score | 1071% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 53-58 cores)</summary>

```
1776876841 53
1776876846 53
1776876851 53
1776876856 57
1776876861 57
1776876866 57
1776876871 57
1776876876 57
1776876881 57
1776876886 57
1776876891 57
1776876896 57
1776876901 58
1776876906 58
1776876911 58
1776876916 58
1776876921 58
1776876926 58
1776876931 58
1776876936 58
```
</details>

---

