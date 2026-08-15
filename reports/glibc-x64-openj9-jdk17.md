---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-15 05:47:13 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 41-81 cores)</summary>

```
1786786970 41
1786786975 41
1786786980 41
1786786985 41
1786786990 41
1786786995 41
1786787000 61
1786787005 61
1786787010 76
1786787015 76
1786787020 76
1786787025 76
1786787030 76
1786787035 76
1786787040 76
1786787045 76
1786787050 76
1786787055 76
1786787060 76
1786787065 76
```
</details>

---

