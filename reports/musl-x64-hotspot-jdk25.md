---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:36:51 EST

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 9-11 cores)</summary>

```
1794569555 9
1794569560 9
1794569565 9
1794569570 9
1794569575 9
1794569580 9
1794569585 9
1794569590 11
1794569595 11
1794569600 11
1794569605 11
1794569610 11
1794569615 11
1794569620 11
1794569625 11
1794569630 11
1794569635 11
1794569640 11
1794569645 11
1794569650 11
```
</details>

---

