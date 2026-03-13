---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-13 07:10:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (4 unique values: 54-70 cores)</summary>

```
1773399952 54
1773399957 54
1773399962 54
1773399967 54
1773399972 54
1773399977 54
1773399982 54
1773399987 54
1773399992 56
1773399997 56
1773400002 56
1773400007 56
1773400012 56
1773400017 56
1773400022 56
1773400027 56
1773400032 70
1773400037 70
1773400042 70
1773400047 70
```
</details>

---

