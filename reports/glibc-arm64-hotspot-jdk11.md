---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:08:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 15 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1789995775 49
1789995780 49
1789995785 49
1789995790 49
1789995795 49
1789995800 49
1789995805 49
1789995810 49
1789995815 49
1789995820 49
1789995825 49
1789995830 49
1789995835 49
1789995840 49
1789995845 49
1789995850 49
1789995855 49
1789995860 49
1789995865 49
1789995870 49
```
</details>

---

