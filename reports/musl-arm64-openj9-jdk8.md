---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 11:25:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1793722739 39
1793722744 39
1793722749 39
1793722754 39
1793722759 39
1793722764 44
1793722769 44
1793722774 44
1793722779 44
1793722784 44
1793722789 44
1793722794 44
1793722799 44
1793722804 44
1793722809 44
1793722814 44
1793722819 44
1793722825 44
1793722830 44
1793722835 44
```
</details>

---

