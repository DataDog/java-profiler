---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 16:54:31 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (8 unique values: 73-85 cores)</summary>

```
1778186922 77
1778186927 73
1778186932 73
1778186937 75
1778186942 75
1778186947 75
1778186952 75
1778186957 75
1778186962 77
1778186967 77
1778186972 77
1778186978 79
1778186983 79
1778186988 79
1778186993 79
1778186998 81
1778187003 81
1778187008 81
1778187013 74
1778187018 74
```
</details>

---

