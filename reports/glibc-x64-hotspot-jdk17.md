---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 18:10:51 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (5 unique values: 51-68 cores)</summary>

```
1795129574 61
1795129579 61
1795129584 61
1795129589 61
1795129594 61
1795129599 51
1795129604 51
1795129609 51
1795129614 51
1795129619 51
1795129624 51
1795129629 53
1795129634 53
1795129639 53
1795129644 53
1795129649 53
1795129654 53
1795129659 53
1795129664 63
1795129669 63
```
</details>

---

