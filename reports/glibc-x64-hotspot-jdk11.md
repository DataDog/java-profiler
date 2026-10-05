---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 16:36:22 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 57-60 cores)</summary>

```
1791232300 58
1791232306 58
1791232311 58
1791232316 58
1791232321 58
1791232326 58
1791232331 58
1791232336 58
1791232341 58
1791232346 58
1791232351 58
1791232356 60
1791232361 60
1791232366 58
1791232371 58
1791232376 58
1791232381 58
1791232386 58
1791232391 58
1791232396 59
```
</details>

---

