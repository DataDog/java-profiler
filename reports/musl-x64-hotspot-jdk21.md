---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 13:50:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1793731427 77
1793731432 77
1793731437 75
1793731442 75
1793731447 75
1793731453 75
1793731458 75
1793731463 75
1793731468 75
1793731473 75
1793731478 75
1793731483 77
1793731488 77
1793731493 79
1793731498 79
1793731503 79
1793731508 79
1793731513 79
1793731518 79
1793731523 81
```
</details>

---

