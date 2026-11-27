---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:43:17 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 66-76 cores)</summary>

```
1795786670 74
1795786675 76
1795786680 76
1795786685 76
1795786690 76
1795786695 76
1795786700 76
1795786705 76
1795786710 76
1795786715 76
1795786720 76
1795786725 76
1795786730 76
1795786735 76
1795786740 76
1795786745 76
1795786750 76
1795786755 76
1795786760 66
1795786765 66
```
</details>

---

