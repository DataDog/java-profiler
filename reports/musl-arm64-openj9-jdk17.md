---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:34:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (4 unique values: 20-44 cores)</summary>

```
1789719894 20
1789719899 20
1789719904 20
1789719909 20
1789719914 20
1789719919 20
1789719924 20
1789719929 20
1789719934 25
1789719939 25
1789719944 25
1789719949 25
1789719954 30
1789719959 30
1789719964 30
1789719969 30
1789719974 44
1789719979 44
1789719984 44
1789719989 44
```
</details>

---

