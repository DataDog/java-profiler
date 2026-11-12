---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 08:26:02 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 80-88 cores)</summary>

```
1794489670 82
1794489675 82
1794489680 82
1794489685 82
1794489690 82
1794489695 80
1794489700 80
1794489705 80
1794489710 80
1794489715 80
1794489720 86
1794489725 86
1794489730 86
1794489735 86
1794489740 86
1794489745 86
1794489750 86
1794489755 86
1794489760 86
1794489765 86
```
</details>

---

