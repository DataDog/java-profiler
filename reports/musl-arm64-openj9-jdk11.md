---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:25:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 29-40 cores)</summary>

```
1793722749 29
1793722754 29
1793722759 29
1793722764 29
1793722769 29
1793722774 29
1793722779 29
1793722784 29
1793722789 29
1793722794 29
1793722799 29
1793722804 29
1793722809 29
1793722814 29
1793722819 29
1793722824 29
1793722829 29
1793722834 29
1793722839 40
1793722844 40
```
</details>

---

