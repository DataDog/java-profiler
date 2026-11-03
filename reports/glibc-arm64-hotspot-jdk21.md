---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 13:50:09 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 36-54 cores)</summary>

```
1793731490 41
1793731495 41
1793731500 41
1793731505 41
1793731510 41
1793731515 41
1793731520 41
1793731525 41
1793731530 41
1793731535 41
1793731540 41
1793731545 41
1793731550 36
1793731555 36
1793731560 36
1793731565 36
1793731570 36
1793731575 36
1793731580 36
1793731585 36
```
</details>

---

