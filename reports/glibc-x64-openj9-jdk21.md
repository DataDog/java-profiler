---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:34:15 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 60-68 cores)</summary>

```
1795613392 60
1795613397 60
1795613402 60
1795613407 60
1795613412 60
1795613417 60
1795613422 60
1795613427 60
1795613432 60
1795613437 60
1795613442 60
1795613447 60
1795613452 60
1795613457 60
1795613462 60
1795613467 60
1795613472 60
1795613477 68
1795613482 68
1795613487 68
```
</details>

---

