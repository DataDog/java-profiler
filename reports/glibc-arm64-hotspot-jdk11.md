---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 11:23:11 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1778512729 57
1778512734 57
1778512739 57
1778512744 57
1778512749 57
1778512754 57
1778512759 57
1778512764 57
1778512769 57
1778512774 57
1778512779 57
1778512784 57
1778512789 57
1778512794 64
1778512799 64
1778512804 64
1778512809 64
1778512814 64
1778512819 53
1778512824 53
```
</details>

---

