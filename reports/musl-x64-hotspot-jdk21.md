---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:56:28 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1795171805 96
1795171810 96
1795171815 96
1795171820 96
1795171825 96
1795171830 96
1795171835 96
1795171840 96
1795171845 96
1795171850 96
1795171855 94
1795171860 94
1795171865 92
1795171870 92
1795171875 92
1795171880 92
1795171885 92
1795171890 92
1795171895 89
1795171900 89
```
</details>

---

