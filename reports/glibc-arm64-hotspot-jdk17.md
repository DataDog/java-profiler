---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:06:19 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 38 |
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
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 25-38 cores)</summary>

```
1795010499 25
1795010504 25
1795010510 25
1795010515 25
1795010520 25
1795010525 25
1795010530 25
1795010535 25
1795010540 25
1795010545 25
1795010550 25
1795010555 25
1795010560 25
1795010565 25
1795010570 38
1795010575 38
1795010580 38
1795010585 38
1795010590 38
1795010595 38
```
</details>

---

