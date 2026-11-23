---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:46:03 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795451827 64
1795451832 64
1795451837 64
1795451842 64
1795451847 64
1795451852 64
1795451857 64
1795451862 64
1795451867 64
1795451872 64
1795451877 64
1795451882 64
1795451887 64
1795451892 64
1795451897 64
1795451902 64
1795451907 64
1795451912 64
1795451917 64
1795451922 64
```
</details>

---

