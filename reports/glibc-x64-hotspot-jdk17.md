---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-11 14:11:47 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 78-84 cores)</summary>

```
1786471595 82
1786471600 84
1786471605 84
1786471610 84
1786471615 84
1786471620 84
1786471625 84
1786471630 84
1786471635 84
1786471640 84
1786471645 84
1786471650 84
1786471655 84
1786471660 78
1786471665 78
1786471670 78
1786471675 78
1786471680 78
1786471685 78
1786471690 78
```
</details>

---

