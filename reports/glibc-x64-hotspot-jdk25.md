---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 11:32:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1794846417 27
1794846422 27
1794846427 27
1794846432 27
1794846437 27
1794846442 29
1794846447 29
1794846452 29
1794846457 29
1794846462 29
1794846467 29
1794846472 29
1794846477 29
1794846482 29
1794846487 29
1794846492 29
1794846497 29
1794846502 29
1794846507 29
1794846512 29
```
</details>

---

