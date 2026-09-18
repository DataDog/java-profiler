---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:34:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 8 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 10-18 cores)</summary>

```
1789719899 10
1789719904 10
1789719909 10
1789719914 18
1789719919 18
1789719924 18
1789719929 18
1789719934 18
1789719939 18
1789719944 18
1789719949 18
1789719954 18
1789719959 18
1789719964 18
1789719969 18
1789719974 18
1789719979 18
1789719984 18
1789719989 18
1789719994 18
```
</details>

---

