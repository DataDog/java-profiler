---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-25 10:31:17 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 64-73 cores)</summary>

```
1790346415 64
1790346420 64
1790346425 73
1790346430 73
1790346435 71
1790346440 71
1790346445 71
1790346450 71
1790346455 71
1790346460 71
1790346465 71
1790346470 71
1790346475 71
1790346480 71
1790346485 71
1790346490 71
1790346495 65
1790346500 65
1790346505 65
1790346510 65
```
</details>

---

