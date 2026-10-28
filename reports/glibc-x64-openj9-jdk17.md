---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 12:04:39 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1793203158 75
1793203163 75
1793203168 75
1793203173 75
1793203178 75
1793203183 75
1793203188 75
1793203193 75
1793203198 75
1793203203 75
1793203208 75
1793203213 75
1793203218 75
1793203223 75
1793203228 76
1793203233 76
1793203238 76
1793203243 76
1793203248 76
1793203253 76
```
</details>

---

