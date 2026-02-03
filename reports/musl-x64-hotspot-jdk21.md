---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 07:53:27 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 903 |
| Sample Rate | 15.05/sec |
| Health Score | 941% |
| Threads | 13 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1770122806 45
1770122811 45
1770122816 45
1770122821 45
1770122826 45
1770122831 45
1770122836 43
1770122841 43
1770122846 43
1770122851 43
1770122856 43
1770122861 43
1770122866 43
1770122871 43
1770122876 43
1770122881 43
1770122886 48
1770122891 48
1770122896 33
1770122901 33
```
</details>

---

