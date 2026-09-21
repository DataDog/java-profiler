---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:08:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1789995735 22
1789995740 22
1789995745 22
1789995750 22
1789995755 22
1789995760 22
1789995765 22
1789995770 22
1789995775 22
1789995780 22
1789995785 22
1789995790 22
1789995795 22
1789995800 32
1789995805 32
1789995810 32
1789995815 32
1789995820 32
1789995825 32
1789995830 32
```
</details>

---

