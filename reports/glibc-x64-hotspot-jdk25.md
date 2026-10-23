---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-23 01:06:18 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 59-96 cores)</summary>

```
1792731630 96
1792731635 96
1792731640 96
1792731645 96
1792731650 96
1792731655 96
1792731660 79
1792731665 79
1792731670 79
1792731675 59
1792731680 59
1792731685 59
1792731690 59
1792731695 59
1792731700 59
1792731705 59
1792731710 59
1792731715 59
1792731720 59
1792731725 59
```
</details>

---

