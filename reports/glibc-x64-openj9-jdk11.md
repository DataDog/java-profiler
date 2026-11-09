---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 15:36:44 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 51-63 cores)</summary>

```
1794256312 56
1794256317 56
1794256322 63
1794256327 63
1794256332 63
1794256337 53
1794256342 53
1794256347 53
1794256352 53
1794256357 53
1794256362 53
1794256367 53
1794256372 53
1794256377 51
1794256382 51
1794256387 61
1794256392 61
1794256397 61
1794256402 61
1794256407 61
```
</details>

---

