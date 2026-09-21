---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:40:55 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 60-84 cores)</summary>

```
1789997729 62
1789997734 62
1789997739 60
1789997744 60
1789997749 60
1789997754 84
1789997759 84
1789997764 74
1789997769 74
1789997774 74
1789997779 74
1789997784 74
1789997789 74
1789997794 74
1789997799 74
1789997804 74
1789997809 74
1789997814 74
1789997819 74
1789997824 74
```
</details>

---

