---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:16:18 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 64-69 cores)</summary>

```
1795691185 66
1795691190 66
1795691195 66
1795691200 66
1795691205 66
1795691210 66
1795691215 66
1795691220 66
1795691225 66
1795691230 69
1795691235 69
1795691240 69
1795691245 69
1795691250 69
1795691255 69
1795691260 69
1795691265 69
1795691270 69
1795691275 69
1795691280 69
```
</details>

---

