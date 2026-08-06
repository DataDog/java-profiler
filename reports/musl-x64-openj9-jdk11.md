---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 11:20:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1037 |
| Sample Rate | 17.28/sec |
| Health Score | 1080% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 63-88 cores)</summary>

```
1786029388 63
1786029393 63
1786029398 63
1786029403 63
1786029408 63
1786029413 63
1786029418 63
1786029423 63
1786029428 63
1786029433 63
1786029438 63
1786029443 63
1786029448 63
1786029453 88
1786029458 88
1786029463 88
1786029468 88
1786029473 88
1786029478 88
1786029483 88
```
</details>

---

