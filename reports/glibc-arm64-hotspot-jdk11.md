---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:13:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 8 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1795097265 45
1795097270 44
1795097275 44
1795097280 44
1795097285 44
1795097290 44
1795097295 44
1795097300 44
1795097305 44
1795097310 44
1795097315 44
1795097320 44
1795097325 44
1795097330 45
1795097335 45
1795097340 43
1795097345 43
1795097350 43
1795097355 43
1795097360 43
```
</details>

---

