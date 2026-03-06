---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-06 04:35:17 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (5 unique values: 54-83 cores)</summary>

```
1772789369 54
1772789374 54
1772789379 54
1772789384 54
1772789389 54
1772789395 55
1772789400 55
1772789405 55
1772789410 77
1772789415 77
1772789420 77
1772789425 77
1772789430 75
1772789435 75
1772789440 75
1772789445 75
1772789450 77
1772789455 77
1772789460 77
1772789465 77
```
</details>

---

