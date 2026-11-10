---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 08:53:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 13-18 cores)</summary>

```
1794318515 18
1794318520 18
1794318525 18
1794318530 18
1794318535 17
1794318540 17
1794318545 17
1794318550 17
1794318555 17
1794318560 17
1794318565 17
1794318570 17
1794318575 17
1794318580 17
1794318585 17
1794318590 17
1794318595 18
1794318600 18
1794318605 13
1794318610 13
```
</details>

---

