---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:25:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 30-64 cores)</summary>

```
1793722784 30
1793722789 30
1793722794 30
1793722799 64
1793722804 64
1793722809 64
1793722814 64
1793722819 30
1793722824 30
1793722829 30
1793722834 30
1793722839 30
1793722844 30
1793722849 30
1793722854 30
1793722859 30
1793722864 30
1793722869 30
1793722874 30
1793722879 30
```
</details>

---

