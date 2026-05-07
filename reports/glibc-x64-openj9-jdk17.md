---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 10:58:43 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (7 unique values: 73-88 cores)</summary>

```
1778165602 82
1778165607 82
1778165612 82
1778165617 82
1778165622 82
1778165627 82
1778165632 82
1778165637 84
1778165642 84
1778165647 84
1778165652 84
1778165657 84
1778165662 88
1778165667 88
1778165672 83
1778165677 83
1778165682 83
1778165687 78
1778165692 78
1778165697 73
```
</details>

---

