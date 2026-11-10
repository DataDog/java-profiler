---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 06:47:20 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 14 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794311015 46
1794311020 46
1794311025 46
1794311030 46
1794311035 46
1794311040 46
1794311045 46
1794311050 46
1794311055 46
1794311060 46
1794311065 46
1794311070 46
1794311075 46
1794311080 51
1794311085 51
1794311090 51
1794311095 51
1794311100 51
1794311105 51
1794311110 51
```
</details>

---

