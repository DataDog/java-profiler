---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 07:09:46 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778151779 64
1778151784 64
1778151789 64
1778151794 64
1778151799 64
1778151804 64
1778151809 64
1778151814 64
1778151819 64
1778151824 64
1778151829 64
1778151834 64
1778151839 64
1778151844 64
1778151849 64
1778151854 64
1778151859 64
1778151864 64
1778151869 64
1778151874 64
```
</details>

---

