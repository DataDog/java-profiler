---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:27:31 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795112660 50
1795112665 64
1795112670 64
1795112675 64
1795112681 64
1795112686 64
1795112691 64
1795112696 64
1795112701 64
1795112706 64
1795112711 64
1795112716 64
1795112721 64
1795112726 64
1795112731 64
1795112736 64
1795112741 64
1795112746 64
1795112751 64
1795112756 64
```
</details>

---

