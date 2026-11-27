---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 10:39:51 EST

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
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1795793651 76
1795793656 76
1795793661 76
1795793666 76
1795793671 76
1795793676 76
1795793681 76
1795793686 76
1795793691 76
1795793696 78
1795793701 78
1795793706 78
1795793711 78
1795793716 78
1795793721 78
1795793726 78
1795793731 78
1795793736 78
1795793741 78
1795793746 78
```
</details>

---

