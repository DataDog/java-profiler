---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 05:38:16 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 896 |
| Sample Rate | 14.93/sec |
| Health Score | 933% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (6 unique values: 85-92 cores)</summary>

```
1794479531 89
1794479536 87
1794479541 87
1794479546 87
1794479551 87
1794479556 87
1794479561 85
1794479566 85
1794479571 88
1794479576 88
1794479581 88
1794479586 88
1794479591 88
1794479596 88
1794479602 88
1794479607 92
1794479612 92
1794479617 92
1794479622 92
1794479627 92
```
</details>

---

