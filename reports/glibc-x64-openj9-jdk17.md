---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-07 18:05:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 10 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 44-66 cores)</summary>

```
1794092422 66
1794092427 46
1794092432 46
1794092437 44
1794092442 44
1794092447 44
1794092452 44
1794092457 44
1794092462 44
1794092467 44
1794092472 44
1794092477 44
1794092482 44
1794092487 46
1794092492 46
1794092497 46
1794092502 46
1794092507 46
1794092512 46
1794092517 46
```
</details>

---

