---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 09:14:02 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 85-94 cores)</summary>

```
1794319700 94
1794319705 94
1794319710 94
1794319715 94
1794319720 94
1794319725 94
1794319730 92
1794319735 92
1794319740 87
1794319745 87
1794319750 87
1794319755 87
1794319760 87
1794319765 87
1794319770 87
1794319775 87
1794319780 87
1794319785 87
1794319790 87
1794319795 87
```
</details>

---

