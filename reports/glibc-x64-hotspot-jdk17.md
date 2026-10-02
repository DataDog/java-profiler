---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-02 14:02:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (6 unique values: 84-90 cores)</summary>

```
1790963894 88
1790963899 86
1790963904 86
1790963909 86
1790963914 84
1790963919 84
1790963924 84
1790963929 84
1790963934 84
1790963939 84
1790963944 86
1790963949 86
1790963954 86
1790963959 90
1790963964 90
1790963969 87
1790963974 87
1790963979 87
1790963984 87
1790963989 87
```
</details>

---

