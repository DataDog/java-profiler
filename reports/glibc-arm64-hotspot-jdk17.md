---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 18:09:54 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1795129545 36
1795129550 36
1795129555 36
1795129560 31
1795129565 31
1795129570 31
1795129575 31
1795129580 31
1795129585 31
1795129590 31
1795129595 31
1795129600 36
1795129605 36
1795129610 36
1795129615 36
1795129620 36
1795129625 36
1795129630 36
1795129635 36
1795129640 36
```
</details>

---

