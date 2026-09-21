---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 00:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 80-81 cores)</summary>

```
1789965834 80
1789965839 80
1789965844 80
1789965849 80
1789965854 80
1789965859 80
1789965864 80
1789965869 80
1789965874 80
1789965879 80
1789965884 80
1789965889 80
1789965894 81
1789965899 81
1789965904 81
1789965909 81
1789965914 81
1789965919 81
1789965924 81
1789965929 81
```
</details>

---

