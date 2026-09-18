---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:50:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 963 |
| Sample Rate | 16.05/sec |
| Health Score | 1003% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 49-58 cores)</summary>

```
1789731819 58
1789731824 58
1789731829 58
1789731834 58
1789731839 58
1789731844 58
1789731849 49
1789731854 49
1789731859 49
1789731864 49
1789731869 49
1789731874 49
1789731879 49
1789731884 49
1789731889 49
1789731894 49
1789731899 49
1789731904 49
1789731909 49
1789731914 49
```
</details>

---

