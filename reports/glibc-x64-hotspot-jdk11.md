---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 08:32:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 44-50 cores)</summary>

```
1791980535 44
1791980540 44
1791980545 44
1791980550 44
1791980555 48
1791980560 48
1791980565 48
1791980570 48
1791980575 48
1791980580 48
1791980585 48
1791980590 48
1791980595 48
1791980600 48
1791980605 48
1791980610 48
1791980615 48
1791980620 48
1791980625 48
1791980630 48
```
</details>

---

