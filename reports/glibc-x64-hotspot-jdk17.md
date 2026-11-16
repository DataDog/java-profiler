---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 08:44:05 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 55-73 cores)</summary>

```
1794836376 55
1794836381 55
1794836386 55
1794836391 55
1794836396 55
1794836401 55
1794836406 55
1794836411 55
1794836416 57
1794836421 57
1794836426 57
1794836431 59
1794836436 59
1794836441 56
1794836446 56
1794836451 56
1794836456 56
1794836461 56
1794836466 56
1794836471 56
```
</details>

---

