---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 07:50:56 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 348 |
| Sample Rate | 5.80/sec |
| Health Score | 362% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 34-67 cores)</summary>

```
1789731824 34
1789731829 34
1789731834 34
1789731839 34
1789731844 34
1789731849 34
1789731854 36
1789731859 36
1789731864 36
1789731869 36
1789731874 67
1789731879 67
1789731884 67
1789731889 67
1789731894 67
1789731899 67
1789731904 67
1789731909 67
1789731914 67
1789731919 65
```
</details>

---

