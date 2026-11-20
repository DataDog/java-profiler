---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:15:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 78-96 cores)</summary>

```
1795194656 81
1795194661 81
1795194666 81
1795194671 81
1795194676 81
1795194681 78
1795194686 78
1795194691 78
1795194696 78
1795194701 78
1795194706 78
1795194711 78
1795194716 81
1795194721 81
1795194726 81
1795194731 81
1795194736 81
1795194741 81
1795194746 81
1795194751 81
```
</details>

---

