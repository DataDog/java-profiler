---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:30:58 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 61-81 cores)</summary>

```
1789719932 61
1789719937 61
1789719942 61
1789719947 81
1789719952 81
1789719957 79
1789719962 79
1789719967 79
1789719972 79
1789719977 79
1789719982 79
1789719987 79
1789719992 79
1789719997 79
1789720002 79
1789720007 79
1789720012 77
1789720017 77
1789720022 77
1789720027 77
```
</details>

---

