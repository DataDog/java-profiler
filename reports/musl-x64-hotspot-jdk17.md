---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 18:13:02 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 848 |
| Sample Rate | 14.13/sec |
| Health Score | 883% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 53-68 cores)</summary>

```
1795129634 53
1795129639 53
1795129644 53
1795129649 53
1795129655 53
1795129660 53
1795129665 63
1795129670 63
1795129675 68
1795129680 68
1795129685 68
1795129690 68
1795129695 68
1795129700 68
1795129705 68
1795129710 68
1795129715 68
1795129720 68
1795129725 68
1795129730 59
```
</details>

---

