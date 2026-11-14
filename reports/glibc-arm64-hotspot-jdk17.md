---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-14 13:57:43 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 10 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794682383 40
1794682388 40
1794682393 40
1794682398 40
1794682403 40
1794682408 40
1794682413 40
1794682418 40
1794682423 40
1794682428 40
1794682433 40
1794682438 40
1794682443 40
1794682448 40
1794682453 40
1794682458 40
1794682463 40
1794682468 40
1794682473 40
1794682478 40
```
</details>

---

