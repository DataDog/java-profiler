---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:30:05 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (5 unique values: 77-94 cores)</summary>

```
1795112632 89
1795112637 89
1795112642 92
1795112647 92
1795112652 94
1795112657 94
1795112662 94
1795112667 94
1795112672 94
1795112677 94
1795112682 77
1795112687 77
1795112692 77
1795112697 77
1795112702 77
1795112707 79
1795112712 79
1795112717 79
1795112722 79
1795112727 79
```
</details>

---

