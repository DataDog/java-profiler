---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 11:25:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 51-55 cores)</summary>

```
1793722748 51
1793722753 51
1793722758 51
1793722763 51
1793722768 51
1793722773 51
1793722778 51
1793722783 53
1793722788 53
1793722793 55
1793722798 55
1793722803 55
1793722808 55
1793722813 55
1793722818 55
1793722823 55
1793722828 55
1793722833 55
1793722838 55
1793722843 55
```
</details>

---

