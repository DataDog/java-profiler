---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 07:53:27 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 12 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (6 unique values: 30-57 cores)</summary>

```
1770122786 30
1770122791 30
1770122796 30
1770122801 30
1770122806 30
1770122811 30
1770122816 47
1770122821 47
1770122826 52
1770122831 52
1770122836 57
1770122841 57
1770122846 51
1770122851 51
1770122856 56
1770122861 56
1770122866 56
1770122871 56
1770122876 56
1770122881 56
```
</details>

---

