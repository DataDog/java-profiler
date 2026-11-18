---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 14:19:56 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (6 unique values: 54-84 cores)</summary>

```
1795029351 79
1795029356 79
1795029361 79
1795029366 79
1795029371 77
1795029376 77
1795029381 77
1795029386 77
1795029391 84
1795029396 84
1795029401 84
1795029406 84
1795029411 84
1795029416 54
1795029421 54
1795029426 56
1795029431 56
1795029436 66
1795029441 66
1795029446 66
```
</details>

---

