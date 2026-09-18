---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 04:34:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 10 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 15-27 cores)</summary>

```
1789719894 27
1789719899 27
1789719904 15
1789719909 15
1789719914 15
1789719919 15
1789719924 15
1789719929 15
1789719934 15
1789719939 15
1789719944 15
1789719949 15
1789719954 15
1789719959 15
1789719964 15
1789719969 15
1789719974 15
1789719979 15
1789719984 15
1789719989 15
```
</details>

---

