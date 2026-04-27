---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 14:34:06 EDT

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
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 827 |
| Sample Rate | 13.78/sec |
| Health Score | 861% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 81-86 cores)</summary>

```
1777314586 86
1777314591 86
1777314596 86
1777314601 86
1777314606 86
1777314611 86
1777314616 86
1777314621 86
1777314626 86
1777314631 86
1777314636 86
1777314641 86
1777314646 86
1777314651 81
1777314656 81
1777314661 81
1777314666 81
1777314671 81
1777314676 81
1777314681 81
```
</details>

---

