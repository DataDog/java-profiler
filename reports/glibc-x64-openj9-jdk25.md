---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 12:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1793203168 86
1793203173 86
1793203178 86
1793203183 86
1793203188 86
1793203193 86
1793203198 86
1793203203 86
1793203208 86
1793203213 86
1793203218 86
1793203223 86
1793203228 86
1793203233 86
1793203238 86
1793203243 86
1793203248 86
1793203253 86
1793203258 86
1793203263 88
```
</details>

---

