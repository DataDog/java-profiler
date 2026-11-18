---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 08:22:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 16-17 cores)</summary>

```
1795007933 17
1795007938 17
1795007943 17
1795007949 17
1795007954 17
1795007959 17
1795007964 17
1795007969 17
1795007974 16
1795007979 16
1795007984 16
1795007989 16
1795007994 16
1795007999 16
1795008004 16
1795008009 16
1795008014 16
1795008019 16
1795008024 17
1795008029 17
```
</details>

---

