---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 11:32:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 52-61 cores)</summary>

```
1794846402 52
1794846407 52
1794846412 52
1794846417 52
1794846422 52
1794846427 52
1794846432 52
1794846437 52
1794846442 61
1794846447 61
1794846452 61
1794846457 61
1794846462 61
1794846467 61
1794846472 61
1794846477 61
1794846482 61
1794846487 57
1794846492 57
1794846497 57
```
</details>

---

