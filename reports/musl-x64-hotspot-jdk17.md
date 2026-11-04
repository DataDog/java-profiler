---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:22:59 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 8-15 cores)</summary>

```
1793830719 15
1793830724 15
1793830729 15
1793830734 15
1793830739 15
1793830744 15
1793830749 13
1793830754 13
1793830759 13
1793830764 13
1793830769 13
1793830774 13
1793830779 8
1793830784 8
1793830789 8
1793830794 8
1793830799 8
1793830804 8
1793830809 8
1793830814 8
```
</details>

---

