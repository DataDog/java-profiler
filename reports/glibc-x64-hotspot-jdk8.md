---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 11:34:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 76-86 cores)</summary>

```
1794587400 86
1794587405 86
1794587410 86
1794587415 86
1794587420 86
1794587425 86
1794587430 86
1794587435 86
1794587440 86
1794587445 86
1794587450 86
1794587455 86
1794587460 84
1794587465 84
1794587470 84
1794587475 84
1794587480 84
1794587485 76
1794587490 76
1794587495 76
```
</details>

---

