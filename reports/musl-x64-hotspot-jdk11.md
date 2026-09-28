---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 09:04:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 66-81 cores)</summary>

```
1790600340 66
1790600345 66
1790600350 66
1790600355 66
1790600360 66
1790600365 66
1790600370 66
1790600375 66
1790600380 66
1790600385 66
1790600390 66
1790600395 66
1790600400 66
1790600405 68
1790600410 68
1790600415 70
1790600420 70
1790600425 70
1790600430 70
1790600435 81
```
</details>

---

