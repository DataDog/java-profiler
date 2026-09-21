---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 07:59:45 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 15-15 cores)</summary>

```
1789991729 15
1789991734 15
1789991739 15
1789991744 15
1789991749 15
1789991754 15
1789991759 15
1789991764 15
1789991769 15
1789991774 15
1789991779 15
1789991784 15
1789991789 15
1789991794 15
1789991799 15
1789991804 15
1789991809 15
1789991814 15
1789991819 15
1789991824 15
```
</details>

---

