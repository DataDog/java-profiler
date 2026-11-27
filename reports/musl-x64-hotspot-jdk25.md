---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 13:25:50 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (5 unique values: 62-66 cores)</summary>

```
1795803628 62
1795803633 62
1795803638 62
1795803643 62
1795803648 62
1795803653 62
1795803658 62
1795803663 62
1795803668 62
1795803673 62
1795803678 64
1795803683 64
1795803688 64
1795803693 64
1795803698 64
1795803703 66
1795803708 66
1795803713 65
1795803718 65
1795803723 63
```
</details>

---

