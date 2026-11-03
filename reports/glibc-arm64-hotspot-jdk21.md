---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:00:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 9 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 30-48 cores)</summary>

```
1793721260 35
1793721265 30
1793721270 30
1793721275 30
1793721280 30
1793721285 30
1793721290 30
1793721295 30
1793721300 30
1793721305 30
1793721310 30
1793721315 30
1793721320 30
1793721325 35
1793721330 35
1793721335 35
1793721340 35
1793721345 35
1793721350 35
1793721355 48
```
</details>

---

