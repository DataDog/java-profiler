---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 11:50:34 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1791215104 75
1791215109 75
1791215114 75
1791215119 77
1791215124 77
1791215129 79
1791215134 79
1791215139 81
1791215144 81
1791215149 81
1791215154 81
1791215159 81
1791215164 81
1791215169 81
1791215174 81
1791215179 81
1791215184 81
1791215189 81
1791215194 79
1791215199 79
```
</details>

---

