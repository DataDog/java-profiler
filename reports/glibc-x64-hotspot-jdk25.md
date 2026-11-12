---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 18:03:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 70-79 cores)</summary>

```
1794524373 70
1794524378 70
1794524383 70
1794524388 70
1794524393 70
1794524398 70
1794524403 77
1794524408 77
1794524413 77
1794524418 77
1794524423 77
1794524428 77
1794524433 77
1794524438 77
1794524443 77
1794524448 77
1794524453 77
1794524458 77
1794524463 77
1794524468 77
```
</details>

---

