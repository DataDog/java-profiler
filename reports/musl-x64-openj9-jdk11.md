---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 16:36:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 71-80 cores)</summary>

```
1791232304 79
1791232309 79
1791232314 79
1791232319 79
1791232324 79
1791232329 79
1791232334 79
1791232339 79
1791232344 79
1791232349 79
1791232354 79
1791232359 79
1791232364 71
1791232369 71
1791232374 71
1791232379 71
1791232384 71
1791232389 71
1791232394 71
1791232399 71
```
</details>

---

