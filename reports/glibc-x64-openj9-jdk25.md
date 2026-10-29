---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 09:35:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (4 unique values: 58-61 cores)</summary>

```
1793280646 60
1793280652 60
1793280657 60
1793280662 60
1793280667 60
1793280672 60
1793280677 60
1793280682 60
1793280687 60
1793280692 60
1793280697 60
1793280702 60
1793280707 58
1793280712 58
1793280717 58
1793280722 58
1793280727 58
1793280732 58
1793280737 58
1793280742 58
```
</details>

---

