---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 05:17:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (5 unique values: 71-78 cores)</summary>

```
1792141958 78
1792141963 78
1792141968 78
1792141973 78
1792141978 78
1792141983 78
1792141988 76
1792141993 76
1792141998 76
1792142003 76
1792142008 76
1792142013 76
1792142018 76
1792142023 76
1792142028 76
1792142034 76
1792142039 75
1792142044 75
1792142049 75
1792142054 75
```
</details>

---

