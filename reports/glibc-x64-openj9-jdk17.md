---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 11:31:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795105575 85
1795105580 85
1795105585 85
1795105590 85
1795105595 85
1795105600 87
1795105605 87
1795105610 87
1795105615 87
1795105621 87
1795105626 87
1795105631 87
1795105636 87
1795105641 87
1795105646 85
1795105651 85
1795105656 85
1795105661 85
1795105666 85
1795105671 85
```
</details>

---

