---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 00:59:13 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1012 |
| Sample Rate | 16.87/sec |
| Health Score | 1054% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (6 unique values: 42-68 cores)</summary>

```
1790139252 54
1790139257 44
1790139262 44
1790139267 44
1790139272 44
1790139277 68
1790139282 68
1790139287 68
1790139292 50
1790139297 50
1790139302 50
1790139307 50
1790139312 50
1790139317 50
1790139322 51
1790139327 51
1790139332 51
1790139337 51
1790139342 42
1790139347 42
```
</details>

---

