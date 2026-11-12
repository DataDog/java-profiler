---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:57:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1794498759 83
1794498764 83
1794498769 83
1794498774 83
1794498779 83
1794498784 83
1794498789 83
1794498794 83
1794498799 83
1794498804 83
1794498809 83
1794498814 83
1794498819 83
1794498824 83
1794498829 83
1794498834 83
1794498839 83
1794498844 81
1794498849 81
1794498854 81
```
</details>

---

