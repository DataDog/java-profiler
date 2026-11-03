---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-03 11:25:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 7-9 cores)</summary>

```
1793722743 9
1793722748 9
1793722753 9
1793722758 9
1793722763 9
1793722768 9
1793722773 9
1793722778 9
1793722783 9
1793722788 9
1793722793 9
1793722798 7
1793722803 7
1793722808 7
1793722813 7
1793722818 7
1793722823 7
1793722828 7
1793722833 7
1793722838 7
```
</details>

---

