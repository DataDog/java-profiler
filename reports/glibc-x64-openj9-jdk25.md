---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:29:05 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 872 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 35-55 cores)</summary>

```
1789737828 55
1789737833 55
1789737838 55
1789737843 55
1789737848 55
1789737853 55
1789737858 55
1789737863 55
1789737868 35
1789737873 35
1789737878 35
1789737883 35
1789737888 35
1789737893 35
1789737898 35
1789737903 35
1789737908 35
1789737913 35
1789737918 35
1789737923 35
```
</details>

---

