---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 09:40:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 35-49 cores)</summary>

```
1789997729 35
1789997734 35
1789997739 35
1789997744 35
1789997749 35
1789997754 35
1789997759 35
1789997764 35
1789997769 35
1789997774 35
1789997779 35
1789997784 35
1789997789 35
1789997794 40
1789997799 40
1789997804 40
1789997809 40
1789997814 49
1789997819 49
1789997824 49
```
</details>

---

