---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:08:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 12-27 cores)</summary>

```
1789995750 27
1789995755 27
1789995760 27
1789995765 27
1789995770 27
1789995775 27
1789995780 27
1789995785 27
1789995790 27
1789995795 27
1789995800 27
1789995805 27
1789995810 27
1789995815 27
1789995820 27
1789995825 27
1789995830 27
1789995835 27
1789995840 27
1789995845 27
```
</details>

---

