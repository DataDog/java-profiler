---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 10:58:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (5 unique values: 70-90 cores)</summary>

```
1778165585 70
1778165590 70
1778165595 70
1778165600 76
1778165605 76
1778165610 76
1778165615 76
1778165620 76
1778165625 76
1778165630 76
1778165635 82
1778165640 82
1778165645 84
1778165650 84
1778165655 84
1778165660 84
1778165665 84
1778165670 90
1778165675 90
1778165680 90
```
</details>

---

