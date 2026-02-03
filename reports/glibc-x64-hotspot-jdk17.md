---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 08:20:09 EST

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
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (5 unique values: 66-72 cores)</summary>

```
1770124595 68
1770124600 68
1770124605 72
1770124610 72
1770124615 69
1770124620 69
1770124625 69
1770124630 69
1770124635 69
1770124640 69
1770124645 69
1770124650 69
1770124655 69
1770124660 69
1770124665 69
1770124670 67
1770124675 67
1770124680 67
1770124685 67
1770124690 67
```
</details>

---

