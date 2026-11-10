---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 17:08:39 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 29-48 cores)</summary>

```
1794348281 29
1794348286 48
1794348291 48
1794348296 48
1794348301 48
1794348306 48
1794348311 48
1794348316 48
1794348321 48
1794348326 48
1794348331 48
1794348336 48
1794348341 48
1794348346 29
1794348351 29
1794348356 29
1794348361 29
1794348366 29
1794348371 29
1794348376 29
```
</details>

---

