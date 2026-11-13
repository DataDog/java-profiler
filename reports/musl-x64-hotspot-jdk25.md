---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 11:01:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 75-79 cores)</summary>

```
1794585397 76
1794585402 76
1794585407 76
1794585412 76
1794585417 76
1794585422 76
1794585427 79
1794585432 79
1794585437 79
1794585442 77
1794585447 77
1794585452 75
1794585457 75
1794585462 75
1794585467 75
1794585472 75
1794585477 77
1794585482 77
1794585487 77
1794585492 77
```
</details>

---

