---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-28 09:37:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (7 unique values: 58-81 cores)</summary>

```
1777383060 61
1777383065 61
1777383070 61
1777383075 58
1777383080 58
1777383085 58
1777383090 58
1777383095 60
1777383100 60
1777383105 60
1777383110 69
1777383115 69
1777383120 69
1777383125 69
1777383130 73
1777383135 73
1777383140 73
1777383145 73
1777383150 73
1777383155 81
```
</details>

---

