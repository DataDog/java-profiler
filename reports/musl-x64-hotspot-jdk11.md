---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 16:24:00 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 71-89 cores)</summary>

```
1794604762 71
1794604767 71
1794604772 71
1794604777 71
1794604782 71
1794604787 71
1794604792 71
1794604798 71
1794604803 71
1794604808 71
1794604813 71
1794604818 71
1794604823 71
1794604828 73
1794604833 73
1794604838 71
1794604843 71
1794604848 87
1794604853 87
1794604858 87
```
</details>

---

