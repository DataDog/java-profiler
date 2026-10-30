---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 11:07:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1793372585 76
1793372590 76
1793372595 76
1793372600 76
1793372605 76
1793372610 76
1793372615 76
1793372620 76
1793372625 76
1793372630 76
1793372635 76
1793372640 76
1793372645 76
1793372650 76
1793372655 76
1793372660 74
1793372665 74
1793372670 74
1793372675 74
1793372680 74
```
</details>

---

