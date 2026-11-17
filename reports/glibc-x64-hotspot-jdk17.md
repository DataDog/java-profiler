---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 07:23:37 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794917947 49
1794917952 49
1794917957 49
1794917962 49
1794917967 49
1794917972 49
1794917977 49
1794917982 49
1794917987 49
1794917992 49
1794917997 49
1794918002 49
1794918007 49
1794918012 51
1794918017 51
1794918022 51
1794918027 51
1794918032 51
1794918037 51
1794918042 51
```
</details>

---

