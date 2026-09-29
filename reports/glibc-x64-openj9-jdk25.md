---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-29 06:43:04 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 34-45 cores)</summary>

```
1790678291 34
1790678296 34
1790678301 34
1790678306 34
1790678311 34
1790678316 34
1790678321 34
1790678326 34
1790678331 34
1790678336 34
1790678341 34
1790678346 34
1790678351 45
1790678356 45
1790678361 45
1790678366 45
1790678371 45
1790678376 45
1790678381 45
1790678386 45
```
</details>

---

