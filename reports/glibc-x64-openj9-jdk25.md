---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-03 21:22:13 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 41-60 cores)</summary>

```
1777857386 41
1777857391 41
1777857396 41
1777857401 41
1777857406 41
1777857411 41
1777857416 41
1777857421 41
1777857426 60
1777857431 60
1777857436 60
1777857441 60
1777857446 60
1777857451 60
1777857456 60
1777857461 60
1777857466 60
1777857471 60
1777857476 60
1777857481 60
```
</details>

---

