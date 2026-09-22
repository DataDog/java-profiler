---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 10:37:00 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (6 unique values: 49-76 cores)</summary>

```
1790087405 50
1790087410 50
1790087415 52
1790087420 52
1790087425 52
1790087430 52
1790087435 52
1790087440 52
1790087445 52
1790087450 52
1790087455 76
1790087460 76
1790087465 76
1790087470 49
1790087475 49
1790087480 49
1790087485 49
1790087490 49
1790087495 49
1790087500 49
```
</details>

---

