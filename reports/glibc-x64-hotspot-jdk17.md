---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 06:08:04 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 50-59 cores)</summary>

```
1795172545 51
1795172550 51
1795172555 51
1795172560 51
1795172565 51
1795172570 51
1795172575 51
1795172580 54
1795172585 54
1795172590 54
1795172595 54
1795172600 59
1795172605 59
1795172610 59
1795172615 50
1795172620 50
1795172625 50
1795172630 50
1795172635 50
1795172640 50
```
</details>

---

