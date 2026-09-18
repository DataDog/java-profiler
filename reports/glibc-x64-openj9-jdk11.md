---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:50:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1319 |
| Sample Rate | 21.98/sec |
| Health Score | 1374% |
| Threads | 12 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1789731824 47
1789731829 47
1789731834 47
1789731839 47
1789731844 47
1789731849 47
1789731854 47
1789731859 49
1789731864 49
1789731869 49
1789731875 49
1789731880 49
1789731885 49
1789731890 49
1789731895 49
1789731900 49
1789731905 49
1789731910 49
1789731915 49
1789731920 49
```
</details>

---

