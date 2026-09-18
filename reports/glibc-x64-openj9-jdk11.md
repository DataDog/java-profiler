---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 08:40:36 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 8 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 81-90 cores)</summary>

```
1789734924 86
1789734929 86
1789734934 86
1789734939 86
1789734944 86
1789734949 86
1789734954 86
1789734959 86
1789734964 86
1789734969 86
1789734974 86
1789734979 86
1789734984 86
1789734989 86
1789734994 82
1789734999 82
1789735004 90
1789735009 90
1789735014 90
1789735019 81
```
</details>

---

