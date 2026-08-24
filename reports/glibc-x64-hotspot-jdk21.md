---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-23 21:24:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1787534389 17
1787534394 17
1787534399 17
1787534404 17
1787534409 17
1787534414 17
1787534419 17
1787534424 17
1787534429 17
1787534434 17
1787534439 17
1787534444 17
1787534449 17
1787534454 17
1787534459 17
1787534464 17
1787534469 15
1787534474 15
1787534479 15
1787534484 15
```
</details>

---

