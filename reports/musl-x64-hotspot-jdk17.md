---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 23.17/sec |
| Health Score | 1448% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1769702690 46
1769702695 46
1769702700 46
1769702705 46
1769702710 46
1769702715 48
1769702720 48
1769702725 48
1769702730 48
1769702735 48
1769702740 48
1769702745 48
1769702750 48
1769702755 48
1769702760 48
1769702765 48
1769702770 48
1769702775 48
1769702780 48
1769702785 48
```
</details>

---

