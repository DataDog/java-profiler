---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-19 22:04:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 10 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 14 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787191255 43
1787191260 43
1787191265 43
1787191270 43
1787191275 43
1787191280 43
1787191285 43
1787191290 43
1787191295 43
1787191300 48
1787191305 48
1787191310 48
1787191315 48
1787191320 48
1787191325 48
1787191330 48
1787191335 48
1787191340 48
1787191345 48
1787191350 48
```
</details>

---

