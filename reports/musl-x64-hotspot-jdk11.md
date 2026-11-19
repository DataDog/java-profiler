---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 18:09:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 58-63 cores)</summary>

```
1795129530 60
1795129535 60
1795129540 60
1795129545 58
1795129550 58
1795129555 58
1795129560 58
1795129565 60
1795129570 60
1795129575 60
1795129580 63
1795129585 63
1795129590 63
1795129595 63
1795129600 63
1795129605 63
1795129610 63
1795129615 63
1795129620 63
1795129625 63
```
</details>

---

