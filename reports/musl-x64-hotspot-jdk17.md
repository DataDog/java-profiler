---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-05 06:41:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 85-91 cores)</summary>

```
1791196544 85
1791196549 85
1791196554 85
1791196559 91
1791196564 91
1791196569 91
1791196574 91
1791196579 91
1791196584 91
1791196589 91
1791196594 91
1791196600 91
1791196605 91
1791196610 91
1791196615 91
1791196620 91
1791196625 91
1791196630 91
1791196635 91
1791196640 91
```
</details>

---

