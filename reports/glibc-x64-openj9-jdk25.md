---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 12:43:40 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 26.07/sec |
| Health Score | 1629% |
| Threads | 11 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 873 |
| Sample Rate | 29.10/sec |
| Health Score | 1819% |
| Threads | 12 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 66-82 cores)</summary>

```
1769708267 66
1769708272 66
1769708277 77
1769708282 77
1769708287 77
1769708292 77
1769708297 77
1769708302 77
1769708307 77
1769708312 77
1769708317 77
1769708322 82
1769708327 82
1769708332 82
1769708337 82
1769708342 82
1769708347 82
1769708352 82
1769708357 82
1769708363 82
```
</details>

---

