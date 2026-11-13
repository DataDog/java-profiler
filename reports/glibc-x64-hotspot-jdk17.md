---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:34:29 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 12 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 74-86 cores)</summary>

```
1794587405 86
1794587410 86
1794587415 86
1794587420 86
1794587425 86
1794587430 76
1794587435 76
1794587440 76
1794587445 76
1794587450 76
1794587455 76
1794587460 76
1794587465 76
1794587470 76
1794587475 76
1794587480 76
1794587485 76
1794587490 76
1794587495 76
1794587500 76
```
</details>

---

