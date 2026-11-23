---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:46:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 920 |
| Sample Rate | 15.33/sec |
| Health Score | 958% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 34-64 cores)</summary>

```
1795451827 34
1795451832 34
1795451837 34
1795451842 34
1795451847 34
1795451852 34
1795451857 34
1795451862 34
1795451867 34
1795451872 34
1795451877 34
1795451882 34
1795451887 34
1795451893 34
1795451898 34
1795451903 34
1795451908 34
1795451913 34
1795451918 34
1795451923 34
```
</details>

---

