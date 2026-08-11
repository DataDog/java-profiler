---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-11 09:27:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 56-68 cores)</summary>

```
1786454485 68
1786454490 68
1786454495 68
1786454500 68
1786454505 68
1786454510 68
1786454515 68
1786454520 68
1786454525 68
1786454530 68
1786454535 68
1786454540 68
1786454545 68
1786454550 68
1786454555 66
1786454560 66
1786454565 66
1786454570 66
1786454575 66
1786454580 56
```
</details>

---

