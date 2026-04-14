---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-14 13:34:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 12 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776187784 59
1776187789 59
1776187794 59
1776187799 59
1776187804 59
1776187809 64
1776187814 64
1776187819 64
1776187824 64
1776187829 64
1776187834 64
1776187839 64
1776187844 64
1776187849 64
1776187854 64
1776187859 64
1776187864 64
1776187869 64
1776187874 64
1776187879 64
```
</details>

---

