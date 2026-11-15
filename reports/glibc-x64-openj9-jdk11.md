---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 16:13:25 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 82-87 cores)</summary>

```
1794776945 82
1794776950 82
1794776955 82
1794776960 82
1794776965 82
1794776970 82
1794776975 82
1794776980 82
1794776985 82
1794776990 82
1794776995 82
1794777000 82
1794777005 82
1794777010 82
1794777015 82
1794777020 82
1794777025 82
1794777030 87
1794777035 87
1794777040 87
```
</details>

---

